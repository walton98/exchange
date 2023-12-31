#include <expected>

#include "request.hpp"

import matcher.types;

namespace matcher::request {

namespace {

constexpr auto parse_side(const types_proto::Side side) {
  switch (side) {
  case types_proto::SIDE_BUY:
    return types::side::buy;
  case types_proto::SIDE_SELL:
    return types::side::sell;
  default:
    std::unreachable();
  }
}

constexpr auto parse_order(const matcher_proto::Order &order) {
  return types::order{order.id(), order.price(), order.quantity(),
                      parse_side(order.side())};
}

} // namespace

constexpr create_book::create_book(const matcher_proto::CreateBook &cb)
    : id_{cb.book().id()} {}

constexpr create_order::create_order(const matcher_proto::CreateOrder &co)
    : book_id_{co.book_id()}, order_{parse_order(co.order())} {}

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
    spdlog::error("Invalid action: {}", env.DebugString());
    return std::unexpected{parse_error::unknown};
  }
}

} // namespace matcher::request
