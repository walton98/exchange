#ifndef MENG_BOOK_REGISTRY_HPP
#define MENG_BOOK_REGISTRY_HPP

#include <unordered_map>

#include "book.hpp"

namespace meng {

class book_registry {
  std::unordered_map<book::book_id, book> books_;

public:
  bool create_book(book::book_id book_id) {
    auto result = books_.insert({book_id, book{book_id}});
    return result.second;
  }
};

} // namespace meng

#endif // MENG_BOOK_REGISTRY_HPP
