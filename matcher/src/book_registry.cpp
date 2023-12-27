#include <book_registry.hpp>

namespace matcher {

auto book_registry::create_book(types::book_id book_id) -> bool {
  auto [_, inserted] = books_.try_emplace(book_id, book::book{});
  return inserted;
}

} // namespace matcher
