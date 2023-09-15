#include <exception>
#include <iostream>
#include <thread>

#include <asio/io_context.hpp>

#include "book_registry.hpp"
#include "consumer.hpp"
#include "engine.hpp"

void run() {

  asio::io_context ioc;
  auto work = asio::make_work_guard(ioc.get_executor());
  auto asio_thread = std::thread([&]() { ioc.run(); });

  constexpr int multicast_port{30001};
  std::string multicast_host{"224.1.1.1"};
  meng::consumer cons{ioc, multicast_port, multicast_host};

  cons.start();

  meng::engine engine {};

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
