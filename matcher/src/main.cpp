#include <exception>
#include <print>
#include <string_view>

#include <common/init.hpp>

#include "engine.hpp"
#include "request.hpp"

import matcher.config;

void run() {
  matcher::engine eng{"matcher-state.xml"};
  constexpr int port{30001};
  constexpr std::string_view host{"224.1.1.1"};
  init::config cfg{init::consumer_config{port, host}};
  init::init<matcher::RingBuf>(std::move(eng), cfg,
                               &matcher::request::parse_action);
  config app_cfg{3};
}

int main() {
  try {
    run();
  } catch (std::exception eptr) {
    std::println("Aborted: {}", eptr.what());
  }
}
