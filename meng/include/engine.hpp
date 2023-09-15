#ifndef MENG_ENGINE_HPP
#define MENG_ENGINE_HPP

#include "book_registry.hpp"

namespace meng {

class engine {
public:
  engine() : books{} {}

private:
  meng::book_registry books;
};

}  // namespace meng

#endif
