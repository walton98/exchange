#ifndef MATCHER_ENGINE_HPP
#define MATCHER_ENGINE_HPP

#include <expected>

#include <matcher.pb.h>

#include "book_registry.hpp"
#include "request.hpp"

namespace matcher {

enum engine_error {
  already_exists,
  invalid_request,
};

class engine {
public:
  engine() : books_{} {}
  [[nodiscard]] std::expected<void, engine_error>
  operator()(const request::create_book &);
  [[nodiscard]] std::expected<void, engine_error>
  operator()(const request::create_order &);
  [[nodiscard]] std::expected<void, engine_error>
  operator()(const std::monostate &) {
    return std::unexpected{engine_error::invalid_request};
  }

private:
  matcher::book_registry books_;
};

} // namespace matcher

#endif
