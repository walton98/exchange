#include <iostream>

#include "book_registry.hpp"

int main() {
  std::cout << "started" << std::endl;
  BookRegistry books{ };
  auto result = books.create_book(3);
  std::cout << "creating book: " << result << std::endl;
  result = books.create_book(3);
  std::cout << "creating book: " << result << std::endl;
}
