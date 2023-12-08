#include <exception>
#include <string_view>

#include <common/init.hpp>

#include "book_registry.hpp"
#include "engine.hpp"
#include "request.hpp"

void run() {
  matcher::engine eng{"matcher-state.xml"};
  constexpr int port{30001};
  constexpr std::string_view host{"224.1.1.1"};
  init::config cfg{init::consumer_config{port, host}};
  init::init<matcher::RingBuf>(std::move(eng), cfg,
                               &matcher::request::parse_action);
}

int main() {
  try {
    run();
  } catch (std::exception eptr) {
    std::cout << eptr.what() << std::endl;
  }
}
