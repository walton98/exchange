#ifndef MATCHER_BOOK_HPP
#define MATCHER_BOOK_HPP

#include <cstdint>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/serialization/nvp.hpp>

#include "order_list.hpp"
#include "types.hpp"

namespace matcher {

namespace book {

class book {
public:
  explicit book(types::book_id id)
      : book_id_{id}, buy_orders_{types::side::buy},
        sell_orders_{types::side::sell} {}

  [[nodiscard]] constexpr auto book_id() const noexcept { return book_id_; }

  [[nodiscard]] const auto begin(types::side side) noexcept {
    return get_order_list(side).begin();
  }

  [[nodiscard]] const auto end(types::side side) noexcept {
    return get_order_list(side).end();
  }

  void insert_order(types::order &&order);

  bool operator<=>(book const &other) const noexcept = default;

  template <typename Archive>
  void serialize(Archive &ar, unsigned int const /*version*/) {
    ar &boost::serialization::make_nvp("book_id", book_id_);
    ar &boost::serialization::make_nvp("buy_orders", buy_orders_);
    ar &boost::serialization::make_nvp("sell_orders", sell_orders_);
  }

private:
  types::book_id book_id_;
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

namespace boost::serialization {

template <typename Archive>
inline void save_construct_data(
    Archive &ar,
    std::pair<types::book_id const, matcher::book::book> const *source,
    unsigned int const /*version*/) {
  matcher::book::book const &book = source->second;
  auto book_id = book.book_id();

  ar << boost::serialization::make_nvp("book_id", book_id);
}

template <typename Archive>
inline void load_construct_data(
    Archive &ar, std::pair<types::book_id const, matcher::book::book> *target,
    unsigned int const /*version*/) {
  types::book_id book_id{};

  ar >> boost::serialization::make_nvp("book_id", book_id);

  new (target) std::pair<types::book_id const, matcher::book::book>{
      std::piecewise_construct, std::make_tuple(book_id),
      std::make_tuple(book_id)};
}

} // namespace boost::serialization

#endif // MATCHER_BOOK_HPP
