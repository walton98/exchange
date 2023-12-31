#ifndef MATCHER_ENGINE_HPP
#define MATCHER_ENGINE_HPP

#include <expected>
#include <fstream>
#include <future>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <matcher.pb.h>

#include "book_registry.hpp"
#include "request.hpp"

import matcher.types;

namespace matcher {

void save_engine_registry(const book_registry &registry,
                          std::string_view filename);

void load_engine_registry(book_registry &registry, std::string_view filename);

enum engine_error {
  already_exists,
  invalid_request,
  snapshot_in_progress,
};

class engine {
public:
  explicit engine(std::string_view snapshot_file)
      : registry_{}, snapshot_file_{snapshot_file}, snapshot_future_{} {}

  engine(const engine &) = delete;
  engine(engine &&) = delete;
  engine &operator=(const engine &) = delete;
  engine &operator=(engine &&) = delete;

  ~engine();

  [[nodiscard]] auto operator()(const request::create_book &)
      -> std::expected<void, engine_error>;

  [[nodiscard]] auto operator()(const request::create_order &)
      -> std::expected<void, engine_error>;

  [[nodiscard]] auto operator()(const request::snapshot &)
      -> std::expected<void, engine_error>;

  [[nodiscard]] auto operator()(const std::monostate &)
      -> std::expected<void, engine_error> {
    return std::unexpected{engine_error::invalid_request};
  }

  constexpr auto &registry() noexcept { return registry_; }

  void restore();

private:
  matcher::book_registry registry_;
  // TODO: support timestamped filenames so as
  //       to not overwrite old snapshots.
  std::string snapshot_file_;
  std::future<void> snapshot_future_;
};

} // namespace matcher

#endif
