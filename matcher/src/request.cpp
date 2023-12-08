#include <expected>
#include <variant>

#include "request.hpp"
#include "types.hpp"

namespace matcher {

namespace request {

namespace {

types::side parse_side(const types_proto::Side side) {
  switch (side) {
  case types_proto::SIDE_BUY:
    return types::side::buy;
  case types_proto::SIDE_SELL:
    return types::side::sell;
  default:
    __builtin_unreachable();
  }
}

types::order parse_order(const matcher_proto::Order &order) {
  return types::order{order.id(), order.price(), order.quantity(),
                      parse_side(order.side())};
}

} // namespace

create_order::create_order(const matcher_proto::CreateOrder &co)
    : book_id_{co.book_id()}, order_{parse_order(co.order())} {}

create_book::create_book(const matcher_proto::CreateBook &cb)
    : id_{cb.book().id()} {}

auto parse_action(const envelope_proto::Envelope &env)
    -> std::expected<request::request_t, parse_error> {
  const auto &action = env.matcher();
  switch (action.action_case()) {
  case matcher_proto::Action::kCreateBook:
    return request::create_book{action.create_book()};
  case matcher_proto::Action::kCreateOrder:
    return request::create_order{action.create_order()};
  case matcher_proto::Action::kSnapshot:
    return request::snapshot{};
  default:
    std::cout << "not set" << std::endl;
    return std::unexpected{parse_error::unknown};
  }
}

} // namespace request

} // namespace matcher
