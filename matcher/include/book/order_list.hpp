#ifndef MATCHER_ORDER_LIST_HPP
#define MATCHER_ORDER_LIST_HPP

#include <forward_list>

#include <boost/serialization/forward_list.hpp>

import matcher.types;

namespace matcher {

namespace book {

class order_list {
public:
  explicit order_list(types::side side) : side_{side} {}

  void insert_order(types::order &&ord);

  [[nodiscard]] auto begin() const noexcept { return order_list_.begin(); }

  [[nodiscard]] auto end() const noexcept { return order_list_.end(); }

  bool operator==(order_list const &other) const noexcept = default;

  template <typename Archive>
  void serialize(Archive &ar, unsigned int const /*version*/) {
    ar &boost::serialization::make_nvp("orders", order_list_);
    ar &boost::serialization::make_nvp("side", side_);
  }

private:
  std::forward_list<types::order> order_list_;
  types::side side_;

  [[nodiscard]] constexpr auto price_is_better(types::price lhs,
                                               types::price rhs) const noexcept
      -> bool;

  [[nodiscard]] auto find_location(const types::order &order) const;
};

} // namespace book

} // namespace matcher

#endif
