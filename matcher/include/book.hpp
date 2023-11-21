#ifndef MATCHER_BOOK_HPP
#define MATCHER_BOOK_HPP

#include <cstdint>
#include <forward_list>
#include <type_traits>
#include <vector>

#include "types.hpp"

namespace matcher {

namespace {

template <types::side S> class order_list {
public:
  void insert_order(types::order &&ord) {
    auto prev = find_location(ord);
    order_list_.insert_after(prev, ord);
  }

  [[nodiscard]] constexpr auto begin() const noexcept {
    return order_list_.begin();
  }
  [[nodiscard]] constexpr auto end() const noexcept {
    return order_list_.end();
  }

private:
  std::forward_list<types::order> order_list_;

  [[nodiscard]] constexpr bool
  price_is_better(types::price lhs, types::price rhs) const noexcept {
    switch (S) {
    case types::side::buy:
      return lhs > rhs;
    case types::side::sell:
      return lhs < rhs;
    default:
      __builtin_unreachable();
    }
  }

  auto find_location(const types::order &order) const {
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
};

} // namespace

class book {
public:
  using book_id = uint64_t;
  book(book_id id) : id{id} {}

  auto begin(types::side side) {
    switch (side) {
    case types::side::buy:
      return buy_orders_.begin();
    case types::side::sell:
      return sell_orders_.begin();
    }
  }

  auto end(types::side side) {
    switch (side) {
    case types::side::buy:
      return buy_orders_.end();
    case types::side::sell:
      return sell_orders_.end();
    }
  }

  void insert_order(types::order &&order) {
    switch (order.side) {
    case types::side::buy:
      buy_orders_.insert_order(std::move(order));
      break;
    case types::side::sell:
      sell_orders_.insert_order(std::move(order));
      break;
    }
  }

private:
  book_id id;
  order_list<types::side::buy> buy_orders_;
  order_list<types::side::sell> sell_orders_;

  [[nodiscard]] auto find_location(const types::order &order) const;
};

} // namespace matcher

#endif // MATCHER_BOOK_HPP
