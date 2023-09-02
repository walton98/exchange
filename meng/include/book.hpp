#ifndef MENG_BOOK_HPP
#define MENG_BOOK_HPP

#include <cstdint>
#include <vector>

#include "order.hpp"

namespace meng {

class book {
public:
  using book_id = uint64_t;
  book(book_id id) : id{id} {}

private:
  book_id id;
  std::vector<order> orders_;
};

} // namespace meng

#endif // MENG_BOOK_HPP
