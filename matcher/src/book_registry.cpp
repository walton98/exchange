#include <book_registry.hpp>

namespace matcher {

bool book_registry::create_book(types::book_id book_id) {
  auto [_, inserted] = books_.try_emplace(book_id, book::book{});
  return inserted;
}

} // namespace matcher
