#include "book.hpp"

namespace matcher {

namespace {

template <types::side S>
auto order_list<S>::find_location(const types::order &order) const {
  auto it = order_list_.before_begin();
  auto prev = it;
  ++it;
  while (true) {
    if (it == order_list_.end() || price_is_better(order.px, it->px)) {
      return prev;
    }
    ++it;
    ++prev;
  }
}

template <types::side S>
constexpr bool order_list<S>::price_is_better(types::price lhs,
                                              types::price rhs) const noexcept {
  switch (S) {
  case types::side::buy:
    return lhs > rhs;
  case types::side::sell:
    return lhs < rhs;
  default:
    __builtin_unreachable();
  }
}

} // namespace

void book::insert_order(types::order &&order) {
  switch (order.side) {
  case types::side::buy:
    buy_orders_.insert_order(std::move(order));
    break;
  case types::side::sell:
    sell_orders_.insert_order(std::move(order));
    break;
  }
}

} // namespace matcher
