#ifndef OMS_ENGINE_HPP
#define OMS_ENGINE_HPP

#include <expected>
#include <string>
#include <string_view>

#include "request.hpp"

namespace oms {

enum engine_error {
  already_exists,
  invalid_request,
  snapshot_in_progress,
};

class engine {
public:
  explicit engine(std::string_view snapshot_file)
      : snapshot_file_{snapshot_file} {}

  void restore() {}

  [[nodiscard]] std::expected<void, engine_error>
  operator()(const request::snapshot &);

  [[nodiscard]] std::expected<void, engine_error>
  operator()(const std::monostate &) {
    return std::unexpected{engine_error::invalid_request};
  }

private:
  std::string snapshot_file_;
};

} // namespace oms

#endif
