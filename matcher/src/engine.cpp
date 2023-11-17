#include "engine.hpp"

namespace matcher {

std::expected<void, engine_error>
engine::operator()(const request::create_book &request) {
  books_.create_book(request.id());
  std::cout << "creating book" << std::endl;
  return {};
}

std::expected<void, engine_error>
engine::operator()(const request::create_order &request) {
  books_.create_book(request.book_id());
  std::cout << "creating order" << std::endl;
  return {};
}

} // namespace matcher
