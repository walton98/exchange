#ifndef MATCHER_HANDLER_HPP
#define MATCHER_HANDLER_HPP

#include <optional>
#include <variant>

#include <matcher.pb.h>
#include <ring_buffer/ring_buffer.hpp>
#include <spdlog/spdlog.h>
#include <types.pb.h>

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

class create_book {
public:
  create_book(const matcher_proto::CreateBook &cb) : id_{cb.book().id()} {}

  [[nodiscard]] constexpr types::book_id id() const noexcept { return id_; }

private:
  types::book_id id_;
  std::string s_;
};

class create_order {
public:
  create_order(const matcher_proto::CreateOrder &co)
      : book_id_{co.book_id()}, order_{parse_order(co.order())} {}

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

} // namespace request

using RingBuf = ring_buffer::ring_buffer<matcher::request::request_t, 4096>;

// TODO: make generic and move into `server` package
class queuer {
public:
  queuer(ring_buffer::producer<RingBuf> prod) : prod_{std::move(prod)} {}

  void operator()(const matcher_proto::Envelope &);

private:
  ring_buffer::producer<RingBuf> prod_;
};

} // namespace matcher

#endif // !MATCHER_HANDLER_HPP
