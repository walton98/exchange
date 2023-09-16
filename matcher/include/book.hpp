#ifndef MATCHER_BOOK_HPP
#define MATCHER_BOOK_HPP

#include <cstdint>
#include <vector>

#include "order.hpp"

namespace matcher {

class book {
public:
  using book_id = uint64_t;
  book(book_id id) : id{id} {}

private:
  book_id id;
  std::vector<order> orders_;
};

} // namespace matcher

#endif // MATCHER_BOOK_HPP
