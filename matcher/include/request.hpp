#ifndef MATCHER_HANDLER_HPP
#define MATCHER_HANDLER_HPP

#include <optional>
#include <variant>

#include <matcher.pb.h>

#include "engine.hpp"
#include "ring_buffer/ring_buffer.hpp"

namespace matcher {

namespace request {

class create_book {
public:
  create_book(const matcher_proto::CreateBook &cb) : id_{cb.book().id()} {}

private:
  types::book_id id_;
};

class create_order {
public:
  create_order(const matcher_proto::CreateOrder &co) : book_id_{co.book_id()} {}

private:
  types::book_id book_id_;
};

using request_t = std::optional<std::variant<create_book, create_order>>;

} // namespace request

using RingBuf = ring_buffer::ring_buffer<matcher::request::request_t, 4096>;

class consumer {
public:
  consumer(ring_buffer::producer<RingBuf> prod) : prod_{std::move(prod)} {}

  void operator()(const std::string &data);

private:
  ring_buffer::producer<RingBuf> prod_;
};

} // namespace matcher

#endif // !MATCHER_HANDLER_HPP
