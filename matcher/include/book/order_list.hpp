#ifndef MATCHER_ORDER_LIST_HPP
#define MATCHER_ORDER_LIST_HPP

#include <algorithm>
#include <forward_list>

#include <boost/serialization/forward_list.hpp>

#include "types.hpp"

// TODO: remove this when upgrading to clang 17+
//       https://reviews.llvm.org/D145172
template <class Tp, class Allocator>
inline auto operator<=>(const std::forward_list<Tp, Allocator> &x,
                        const std::forward_list<Tp, Allocator> &y) {
  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end(),
                                      std::compare_three_way{});
}

namespace matcher {

namespace book {

class order_list {
public:
  explicit order_list(types::side side) : side_{side} {}

  void insert_order(types::order &&ord);

  [[nodiscard]] auto begin() const noexcept { return order_list_.begin(); }

  [[nodiscard]] auto end() const noexcept { return order_list_.end(); }

  bool operator<=>(order_list const &other) const noexcept = default;

  template <typename Archive>
  void serialize(Archive &ar, unsigned int const /*version*/) {
    ar &boost::serialization::make_nvp("orders", order_list_);
    ar &boost::serialization::make_nvp("side", side_);
  }

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
