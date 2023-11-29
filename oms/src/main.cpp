#include <exception>
#include <iostream>
#include <thread>

#include <asio/io_context.hpp>
#include <ring_buffer/ring_buffer.hpp>
#include <spdlog/spdlog.h>

#include <server/consumer.hpp>
#include <server/layers.hpp>

#include "request.hpp"

auto create_consumer(asio::io_context &ioc, auto &prod) {
  constexpr int multicast_port{30002};
  std::string multicast_host{"224.1.1.2"};

  // Create handler layers
  auto queuer = [](const auto &env) { spdlog::info("Got message"); };
  // TODO: pass in next seqnum from restore
  auto sequencer = server::sequencer<decltype(queuer)>{std::move(queuer)};
  auto decoder = server::decoder{std::move(sequencer)};

  return server::consumer{ioc, multicast_port, multicast_host,
                          std::move(decoder)};
}

void run() {
  spdlog::set_level(spdlog::level::debug);

  // oms::engine engine{"state.xml"};
  // engine.restore();

  asio::io_context ioc;
  auto work = asio::make_work_guard(ioc.get_executor());
  auto asio_thread = std::thread([&]() { ioc.run(); });

  oms::RingBuf buf;
  ring_buffer::cursor_pair cursors{};
  ring_buffer::producer prod{buf, cursors.prod_cursor};

  auto cons = create_consumer(ioc, prod);
  cons.start();

  // auto handler_thread = std::thread([&]() {
  //   for (const auto batch :
  //        ring_buffer::batch_iterate(buf, cursors.cons_cursor, 32)) {
  //     for (const auto &action : batch) {
  //       auto result = std::visit(engine, action);
  //     }
  //   }
  // });

  work.reset();
  asio_thread.join();
}

int main() {
  try {
    run();
  } catch (std::exception eptr) {
    std::cout << eptr.what() << std::endl;
  }
}
