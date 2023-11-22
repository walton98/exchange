#include <book/book.hpp>

namespace matcher {

namespace book {

void book::insert_order(types::order &&order) {
  get_order_list(order.side).insert_order(std::move(order));
}

} // namespace book

} // namespace matcher
