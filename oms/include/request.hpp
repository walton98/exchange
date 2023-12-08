#ifndef OMS_REQUEST_HPP
#define OMS_REQUEST_HPP

#include <expected>
#include <optional>
#include <variant>

#include <envelope.pb.h>
#include <ring_buffer/ring_buffer.hpp>

namespace oms {

namespace request {

class snapshot {};

using request_t = std::variant<std::monostate, snapshot>;

enum class parse_error {
  unknown,
};

auto parse_action(const envelope_proto::Envelope &env)
    -> std::expected<request::request_t, parse_error>;

} // namespace request

using RingBuf = ring_buffer::ring_buffer<request::request_t, 4096>;

} // namespace oms

#endif // !OMS_REQUEST_HPP
