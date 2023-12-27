#ifndef MATCHER_BOOK_REGISTRY_HPP
#define MATCHER_BOOK_REGISTRY_HPP

#include <unordered_map>

#include <boost/serialization/unordered_map.hpp>

#include "book/book.hpp"

namespace matcher {

class book_registry {
  std::unordered_map<types::book_id, book::book> books_;

public:
  auto create_book(types::book_id book_id) -> bool;

  [[nodiscard]] constexpr auto &get_book(types::book_id book_id) {
    return books_.at(book_id);
  }

  template <typename Archive>
  void serialize(Archive &ar, const unsigned int /*version*/) {
    ar &boost::serialization::make_nvp("books", books_);
  }
};

} // namespace matcher

#endif // MATCHER_BOOK_REGISTRY_HPP
