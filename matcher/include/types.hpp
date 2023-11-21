#ifndef MATCHER_TYPES_HPP
#define MATCHER_TYPES_HPP

#include <cstdint>

// TODO: move into separate shared library
namespace types {

using price = uint64_t;
using quantity = uint64_t;
using book_id = uint64_t;
using order_id_t = uint64_t;

enum class side {
  buy,
  sell,
};

struct order {
  types::order_id_t id;
  types::price px;
  types::quantity qty;
  types::side side;
};

} // namespace types

#endif // MATCHER_TYPES_HPP
