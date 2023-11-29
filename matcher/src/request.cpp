#include <expected>
#include <variant>

#include "request.hpp"
#include "types.hpp"

namespace matcher {

namespace {

enum class parse_error {
  unknown,
};

auto handle_message(const matcher_proto::Action &action)
    -> std::expected<request::request_t, parse_error> {
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

} // namespace

void queuer::operator()(const matcher_proto::Envelope &envelope) {
  // TODO: handle unexpected
  auto parsed_action = handle_message(envelope.action()).value();

  // send to ring buffer
  prod_.produce_one(parsed_action);
  prod_.commit();
}

} // namespace matcher
