#ifndef MATCHER_BOOK_HPP
#define MATCHER_BOOK_HPP

#include <utility>

#include <boost/serialization/nvp.hpp>

#include "order_list.hpp"

import matcher.types;

namespace matcher {

namespace book {

class book {
public:
  book() : buy_orders_{types::side::buy}, sell_orders_{types::side::sell} {}

private:
  [[nodiscard]] auto &get_order_list(types::side side) noexcept {
    switch (side) {
    case types::side::buy:
      return buy_orders_;
    case types::side::sell:
      return sell_orders_;
    default:
      std::unreachable();
    }
  }

public:
  [[nodiscard]] const auto begin(types::side side) noexcept {
    return get_order_list(side).begin();
  }

  [[nodiscard]] const auto end(types::side side) noexcept {
    return get_order_list(side).end();
  }

  void insert_order(types::order &&order);

  bool operator==(book const &other) const noexcept = default;

  template <typename Archive>
  void serialize(Archive &ar, unsigned int const /*version*/) {
    ar &boost::serialization::make_nvp("buy_orders", buy_orders_);
    ar &boost::serialization::make_nvp("sell_orders", sell_orders_);
  }

private:
  order_list buy_orders_;
  order_list sell_orders_;
};

} // namespace book

} // namespace matcher

namespace boost::serialization {

template <typename Archive>
inline void save_construct_data(
    Archive &ar,
    std::pair<types::book_id const, matcher::book::book> const *source,
    unsigned int const /*version*/) {
  auto book_id = source->first;
  ar << BOOST_SERIALIZATION_NVP(book_id);
}

template <typename Archive>
inline void load_construct_data(
    Archive &ar, std::pair<types::book_id const, matcher::book::book> *target,
    unsigned int const /*version*/) {
  types::book_id book_id{};
  ar >> BOOST_SERIALIZATION_NVP(book_id);

  new (target) std::pair<types::book_id const, matcher::book::book>{
      std::piecewise_construct, std::make_tuple(book_id), std::make_tuple()};
}

} // namespace boost::serialization

#endif // MATCHER_BOOK_HPP
