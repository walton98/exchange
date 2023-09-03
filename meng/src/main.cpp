#include <iostream>
#include <thread>

#include <asio/io_context.hpp>

#include "book_registry.hpp"
#include "consumer.hpp"

int main() {

  std::cout << "started" << std::endl;
  meng::book_registry books{};
  auto result = books.create_book(3);
  std::cout << "creating book: " << result << std::endl;
  result = books.create_book(3);
  std::cout << "creating book: " << result << std::endl;

  asio::io_context ioc;
  auto work = asio::make_work_guard(ioc.get_executor());
  auto asio_thread = std::thread([&]() { ioc.run(); });

  meng::consumer cons{ioc};
  cons.start();

  work.reset();
  asio_thread.join();
}
