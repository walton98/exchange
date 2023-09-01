#include <cstdint>
#include <vector>

#include "order.hpp"

using BookId = uint64_t;

class Book {
  BookId id;
  std::vector<Order> orders_;
public:
  Book(BookId id) : id{id} {}
};
