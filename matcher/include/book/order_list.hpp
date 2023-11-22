#ifndef MATCHER_ORDER_LIST_HPP
#define MATCHER_ORDER_LIST_HPP

#include <forward_list>

#include "types.hpp"

namespace matcher {

namespace book {

class order_list {
public:
  explicit order_list(types::side side) : side_{side} {}

  void insert_order(types::order &&ord);

  [[nodiscard]] auto begin() const noexcept { return order_list_.begin(); }

  [[nodiscard]] auto end() const noexcept { return order_list_.end(); }

private:
  std::forward_list<types::order> order_list_;
  types::side side_;

  [[nodiscard]] constexpr bool price_is_better(types::price lhs,
                                               types::price rhs) const noexcept;

  [[nodiscard]] auto find_location(const types::order &order) const;
};

} // namespace book

} // namespace matcher

#endif
