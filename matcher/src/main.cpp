#include <exception>
#include <iostream>
#include <thread>

#include <asio/io_context.hpp>
#include <ring_buffer/ring_buffer.hpp>

#include "book_registry.hpp"
#include "consumer.hpp"
#include "engine.hpp"
#include "handler.hpp"

void run() {

  asio::io_context ioc;
  auto work = asio::make_work_guard(ioc.get_executor());
  auto asio_thread = std::thread([&]() { ioc.run(); });

  ring_buffer::ring_buffer<matcher_proto::Action, 4096> buf;
  ring_buffer::cursor_pair cursors{};
  ring_buffer::producer prod{buf, cursors.prod_cursor};

  constexpr int multicast_port{30001};
  std::string multicast_host{"224.1.1.1"};
  matcher::consumer cons{ioc, multicast_port, multicast_host, prod};
  cons.start();

  matcher::engine engine{};
  auto handler_thread = std::thread([&]() {
    for (auto batch :
         ring_buffer::batch_iterate(buf, cursors.cons_cursor, 32)) {
      for (auto const &action : batch) {
        matcher::handle_message(engine, action);
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
