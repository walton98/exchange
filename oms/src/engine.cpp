#include <spdlog/spdlog.h>

#include <engine.hpp>

namespace oms {

std::expected<void, engine_error>
engine::operator()(const request::snapshot &request) {
  // TODO: implement snapshotting
  spdlog::info("Creating snapshot");
  return {};
}

} // namespace oms
