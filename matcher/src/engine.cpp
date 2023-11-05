#include "engine.hpp"

namespace matcher {

std::expected<void, engine_error>
engine::create_book(const matcher_proto::Book &book) {
  books_.create_book(book.id());
  return {};
}

} // namespace matcher
