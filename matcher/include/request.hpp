#ifndef MATCHER_HANDLER_HPP
#define MATCHER_HANDLER_HPP

#include <expected>
#include <variant>

#include <envelope.pb.h>
#include <matcher.pb.h>
#include <ring_buffer/ring_buffer.hpp>
#include <spdlog/spdlog.h>
#include <types.pb.h>

import matcher.types;

namespace matcher {

namespace request {

class create_book {
public:
  explicit constexpr create_book(const matcher_proto::CreateBook &);

  [[nodiscard]] constexpr types::book_id id() const noexcept { return id_; }

private:
  types::book_id id_;
};

class create_order {
public:
  explicit constexpr create_order(const matcher_proto::CreateOrder &);

  [[nodiscard]] constexpr types::book_id book_id() const noexcept {
    return book_id_;
  };

  [[nodiscard]] constexpr types::order order() const noexcept {
    return order_;
  };

private:
  types::book_id book_id_;
  types::order order_;
};

class snapshot {};

using request_t =
    std::variant<std::monostate, create_book, create_order, snapshot>;

enum class parse_error {
  unknown,
};

auto parse_action(const envelope_proto::Envelope &action)
    -> std::expected<request::request_t, parse_error>;

} // namespace request

using RingBuf = ring_buffer::ring_buffer<matcher::request::request_t, 4096>;

} // namespace matcher

#endif // !MATCHER_HANDLER_HPP
