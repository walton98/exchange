#ifndef MATCHER_HANDLER_HPP
#define MATCHER_HANDLER_HPP

#include <matcher.pb.h>

#include "engine.hpp"

namespace matcher {

void handle_message(engine &eng, const matcher_proto::Action &);

} // namespace matcher

#endif // !MATCHER_HANDLER_HPP
