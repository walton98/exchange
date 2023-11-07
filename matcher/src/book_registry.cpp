#include <book_registry.hpp>

namespace matcher {

bool book_registry::create_book(book::book_id book_id) {
  auto [_, inserted] = books_.try_emplace(book_id, book{book_id});
  return inserted;
}

} // namespace matcher