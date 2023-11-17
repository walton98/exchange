#ifndef MATCHER_BOOK_REGISTRY_HPP
#define MATCHER_BOOK_REGISTRY_HPP

#include <unordered_map>

#include "book.hpp"

namespace matcher {

class book_registry {
  std::unordered_map<book::book_id, book> books_;

public:
  bool create_book(book::book_id book_id);

  [[nodiscard]] constexpr auto &get_book(book::book_id book_id) {
    return books_.at(book_id);
  }
};

} // namespace matcher

#endif // MATCHER_BOOK_REGISTRY_HPP
