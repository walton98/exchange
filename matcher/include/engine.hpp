#ifndef MATCHER_ENGINE_HPP
#define MATCHER_ENGINE_HPP

#include <expected>

#include <matcher.pb.h>

#include "book_registry.hpp"

namespace matcher {

enum engine_error {
  already_exists,
};

class engine {
public:
  engine() : books_{} {}
  std::expected<void, engine_error> create_book(const matcher_proto::Book &);

private:
  matcher::book_registry books_;
};

} // namespace matcher

#endif
