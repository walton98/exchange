module;

#include <cstdint>

#include <boost/serialization/nvp.hpp>

export module matcher.types;

// TODO: move into separate shared library
export namespace types {

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

  constexpr bool operator==(order const &other) const noexcept = default;
};

} // namespace types

export namespace boost::serialization {

template <class Archive>
inline void serialize(Archive &ar, types::order &order,
                      const unsigned int /* version */) {
  ar &boost::serialization::make_nvp("order_id", order.order_id);
  ar &boost::serialization::make_nvp("price", order.price);
  ar &boost::serialization::make_nvp("quantity", order.quantity);
  ar &boost::serialization::make_nvp("side", order.side);
}

} // namespace boost::serialization
