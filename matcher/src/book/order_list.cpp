#include <book/order_list.hpp>

namespace matcher {

namespace book {

auto order_list::find_location(const types::order &order) const {
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

void order_list::insert_order(types::order &&ord) {
  auto prev = find_location(ord);
  order_list_.insert_after(prev, ord);
}

constexpr bool order_list::price_is_better(types::price lhs,
                                           types::price rhs) const noexcept {
  switch (side_) {
  case types::side::buy:
    return lhs > rhs;
  case types::side::sell:
    return lhs < rhs;
  default:
    __builtin_unreachable();
  }
}

} // namespace book

} // namespace matcher
