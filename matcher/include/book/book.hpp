#ifndef MATCHER_BOOK_HPP
#define MATCHER_BOOK_HPP

#include <cstdint>
#include <type_traits>
#include <vector>

#include "order_list.hpp"
#include "types.hpp"

namespace matcher {

namespace book {

class book {
public:
  book(types::book_id id)
      : id{id}, buy_orders_{types::side::buy}, sell_orders_{types::side::sell} {
  }

  [[nodiscard]] const auto begin(types::side side) noexcept {
    return get_order_list(side).begin();
  }

  [[nodiscard]] const auto end(types::side side) noexcept {
    return get_order_list(side).end();
  }

  void insert_order(types::order &&order);

private:
  types::book_id id;
  order_list buy_orders_;
  order_list sell_orders_;

  [[nodiscard]] order_list &get_order_list(types::side side) noexcept {
    switch (side) {
    case types::side::buy:
      return buy_orders_;
    case types::side::sell:
      return sell_orders_;
    default:
      __builtin_unreachable();
    }
  }
};

} // namespace book

} // namespace matcher

#endif // MATCHER_BOOK_HPP
