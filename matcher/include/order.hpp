#ifndef MATCHER_ORDER_HPP
#define MATCHER_ORDER_HPP

#include "types.hpp"

namespace matcher {

struct order {
  types::price px;
  types::quantity qty;
};

} // namespace matcher

#endif // MATCHER_ORDER_HPP
