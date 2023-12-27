#ifndef COMMON_INIT_HPP
#define COMMON_INIT_HPP

#include <iostream>
#include <string_view>
#include <thread>
#include <variant>

#include <asio/co_spawn.hpp>
#include <asio/io_context.hpp>
#include <network/consumer.hpp>
#include <network/layers.hpp>
#include <network/producer.hpp>
#include <ring_buffer/ring_buffer.hpp>
#include <spdlog/spdlog.h>

namespace init {

struct consumer_config {
  asio::ip::port_type mcast_port;
  std::string_view mcast_host;
};

struct config {
  consumer_config consumer;
};

namespace detail {

template <typename RingBuf, typename F>
auto create_consumer(asio::io_context &ioc,
                     ring_buffer::producer<RingBuf> &prod,
                     const consumer_config &cfg, F &&request_parser) {
  // Create handler layers
  auto queuer = network::queuer{prod, std::forward<F>(request_parser)};
  // TODO: pass in next seqnum from restore
  auto sequencer = network::sequencer<decltype(queuer)>{std::move(queuer)};
  auto decoder = network::decoder{std::move(sequencer)};

  return network::consumer{ioc, cfg.mcast_port, cfg.mcast_host,
                           std::move(decoder)};
}

} // namespace detail

template <typename RingBuf, typename Engine, typename F>
void init(Engine &&engine, const config &cfg, F &&request_parser) {
  spdlog::set_level(spdlog::level::debug);

  engine.restore();

  asio::io_context ioc;
  auto work = asio::make_work_guard(ioc.get_executor());
  auto asio_thread = std::thread([&]() { ioc.run(); });

  network::producer p{ioc, "224.1.1.1", "30007"};
  // Temporarily send test data on startup
  std::vector<char> data = {'p', 'o', 'o', 'p'};
  asio::co_spawn(ioc, p.produce(data), [](std::exception_ptr eptr) {
    if (eptr) {
      try {
        std::rethrow_exception(eptr);
      } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        ;
      }
    }
  });

  RingBuf buf;
  ring_buffer::cursor_pair cursors{};
  ring_buffer::producer prod{buf, cursors.prod_cursor};

  auto cons = detail::create_consumer(ioc, prod, cfg.consumer,
                                      std::forward<F>(request_parser));
  cons.start();

  auto handler_thread = std::thread([&]() {
    for (const auto batch :
         ring_buffer::batch_iterate(buf, cursors.cons_cursor, 32)) {
      for (const auto &action : batch) {
        auto result = std::visit(engine, action);
      }
    }
  });

  work.reset();
  asio_thread.join();
  handler_thread.join();
}

} // namespace init

#endif
