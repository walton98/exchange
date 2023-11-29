#ifndef OMS_REQUEST_HPP
#define OMS_REQUEST_HPP

#include <optional>
#include <variant>

#include <ring_buffer/ring_buffer.hpp>

namespace oms {

namespace request {

class snapshot {};

using request_t = std::variant<std::monostate, snapshot>;

} // namespace request

using RingBuf = ring_buffer::ring_buffer<request::request_t, 4096>;

} // namespace oms

#endif // !OMS_REQUEST_HPP
