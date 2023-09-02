#ifndef MENG_ORDER_HPP
#define MENG_ORDER_HPP

#include "types.hpp"

namespace meng {

struct order {
  types::price px;
  types::quantity qty;
};

} // namespace meng

#endif // MENG_ORDER_HPP
