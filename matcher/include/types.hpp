#ifndef MATCHER_TYPES_HPP
#define MATCHER_TYPES_HPP

#include <cstdint>

#include <boost/serialization/nvp.hpp>

// TODO: move into separate shared library
namespace types {

using price = uint64_t;
using quantity = uint64_t;
using book_id = uint64_t;
using order_id = uint64_t;

enum class side {
  buy,
  sell,
};

struct order {
  types::order_id order_id;
  types::price price;
  types::quantity quantity;
  types::side side;

  bool operator<=>(order const &other) const noexcept = default;
};

} // namespace types

namespace boost::serialization {

template <class Archive>
inline void serialize(Archive &ar, types::order &order,
                      const unsigned int /* version */) {
  ar &boost::serialization::make_nvp("order_id", order.order_id);
  ar &boost::serialization::make_nvp("price", order.price);
  ar &boost::serialization::make_nvp("quantity", order.quantity);
  ar &boost::serialization::make_nvp("side", order.side);
}

} // namespace boost::serialization

#endif // MATCHER_TYPES_HPP
