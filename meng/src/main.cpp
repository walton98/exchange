#include <exception>
#include <iostream>
#include <thread>

#include <asio/io_context.hpp>

#include "book_registry.hpp"
#include "consumer.hpp"
#include "engine.hpp"
#include "ring_buffer.hpp"

void run() {

  asio::io_context ioc;
  auto work = asio::make_work_guard(ioc.get_executor());
  auto asio_thread = std::thread([&]() { ioc.run(); });

  meng::ring_buffer<meng_proto::Book, 4096> buf;
  meng::cursor_pair cursors{};
  meng::producer prod{buf, cursors.prod_cursor};

  constexpr int multicast_port{30001};
  std::string multicast_host{"224.1.1.1"};
  meng::consumer cons{ioc, multicast_port, multicast_host, prod};
  cons.start();

  meng::engine engine{};
  auto handler_thread = std::thread([&]() {
    for (auto val : meng::batch_iterate(buf, cursors.cons_cursor, 32)) {
      std::cout << "got id: " << val.id() << std::endl;
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
