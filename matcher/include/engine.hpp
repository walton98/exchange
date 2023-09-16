#ifndef MATCHER_ENGINE_HPP
#define MATCHER_ENGINE_HPP

#include "book_registry.hpp"

namespace matcher {

class engine {
public:
  engine() : books{} {}

private:
  matcher::book_registry books;
};

} // namespace matcher

#endif
