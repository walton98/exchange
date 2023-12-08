#include "request.hpp"

namespace oms::request {

auto parse_action(const envelope_proto::Envelope &env)
    -> std::expected<request::request_t, parse_error> {
  return snapshot{};
}

} // namespace oms::request
