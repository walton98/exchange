#include <variant>

#include "handler.hpp"
#include "types.hpp"

namespace matcher {

void handle_message(engine &eng, const matcher_proto::Action &action) {
  switch (action.action_case()) {
  case matcher_proto::Action::kCreateBook:
    eng.create_book(action.create_book().book());
    std::cout << "created book" << std::endl;
    break;
  case matcher_proto::Action::kCreateOrder:
    std::cout << "got create_order" << std::endl;
    break;
  case matcher_proto::Action::ACTION_NOT_SET:
    std::cout << "not set" << std::endl;
    break;
  }
}

} // namespace matcher
