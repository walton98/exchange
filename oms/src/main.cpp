#include <exception>
#include <print>

#include <asio/io_context.hpp>
#include <ring_buffer/ring_buffer.hpp>
#include <spdlog/spdlog.h>

#include <common/init.hpp>
#include <server/consumer.hpp>
#include <server/layers.hpp>

#include <engine.hpp>
#include <request.hpp>

void run() {
  oms::engine eng{"oms-state.xml"};
  constexpr int port{30002};
  constexpr std::string_view host{"224.1.1.1"};
  init::config cfg{init::consumer_config{port, host}};
  init::init<oms::RingBuf>(std::move(eng), cfg, &oms::request::parse_action);
}

int main() {
  try {
    run();
  } catch (std::exception eptr) {
    std::println("Aborted: {}", eptr.what());
  }
}
