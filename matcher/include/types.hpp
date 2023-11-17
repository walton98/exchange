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

} // namespace types

#endif // MATCHER_TYPES_HPP
