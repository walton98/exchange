#include <exception>
#include <iostream>
#include <thread>

#include <asio/io_context.hpp>
#include <ring_buffer/ring_buffer.hpp>
#include <spdlog/spdlog.h>

#include <server/consumer.hpp>

#include "book_registry.hpp"
#include "engine.hpp"
#include "request.hpp"

auto create_consumer(asio::io_context &ioc, auto &prod) {
  constexpr int multicast_port{30001};
  std::string multicast_host{"224.1.1.1"};

  // Create handler layers
  auto queuer = matcher::queuer{prod};
  auto sequencer = matcher::sequencer<matcher::queuer, matcher_proto::Action>{
      std::move(queuer)};
  auto decoder = matcher::decoder{std::move(sequencer)};

  return server::consumer{ioc, multicast_port, multicast_host,
                          std::move(decoder)};
}

void run() {
  spdlog::set_level(spdlog::level::debug);
  matcher::engine engine{"state.xml"};
  engine.restore();

  asio::io_context ioc;
  auto work = asio::make_work_guard(ioc.get_executor());
  auto asio_thread = std::thread([&]() { ioc.run(); });

  matcher::RingBuf buf;
  ring_buffer::cursor_pair cursors{};
  ring_buffer::producer prod{buf, cursors.prod_cursor};

  auto cons = create_consumer(ioc, prod);
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

int main() {
  try {
    run();
  } catch (std::exception eptr) {
    std::cout << eptr.what() << std::endl;
  }
}
