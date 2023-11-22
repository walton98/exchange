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
  auto &book = books_.get_book(request.book_id());
  book.insert_order(request.order());
  std::cout << "creating order" << std::endl;
  return {};
}

std::expected<void, engine_error>
engine::operator()(const request::snapshot &request) {
  std::cout << "snapshotting" << std::endl;
  return {};
}

} // namespace matcher
