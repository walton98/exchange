#ifndef COMMON_INIT_HPP
#define COMMON_INIT_HPP

#include <string_view>
#include <thread>
#include <variant>

#include <asio/io_context.hpp>
#include <ring_buffer/ring_buffer.hpp>
#include <server/consumer.hpp>
#include <server/layers.hpp>
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
  auto queuer = server::queuer{prod, std::forward<F>(request_parser)};
  // TODO: pass in next seqnum from restore
  auto sequencer = server::sequencer<decltype(queuer)>{std::move(queuer)};
  auto decoder = server::decoder{std::move(sequencer)};

  return server::consumer{ioc, cfg.mcast_port, cfg.mcast_host,
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
