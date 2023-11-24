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

namespace matcher {

inline void save_engine_registry(const book_registry &reg,
                                 std::string_view filename) {
  auto ofs = std::ofstream(filename);
  boost::archive::xml_oarchive oa(ofs);
  oa << boost::serialization::make_nvp("registry", reg);
}

inline auto load_engine_registry(book_registry &reg,
                                 std::string_view filename) {
  if (!std::filesystem::exists(filename)) {
    std::cout << "missing state file" << std::endl;
    return;
  }

  std::cout << "restoring from state file" << std::endl;
  auto ifs = std::ifstream(filename);
  boost::archive::xml_iarchive ia(ifs);
  ia >> boost::serialization::make_nvp("registry", reg);
}

enum engine_error {
  already_exists,
  invalid_request,
  snapshot_in_progress,
};

class engine {
public:
  explicit engine(std::string_view snapshot_file)
      : books_{}, snapshot_file_{snapshot_file}, snapshot_future_{} {}

  engine(const engine &) = delete;
  engine(engine &&) = delete;
  engine &operator=(const engine &) = delete;
  engine &operator=(engine &&) = delete;

  ~engine();

  [[nodiscard]] std::expected<void, engine_error>
  operator()(const request::create_book &);

  [[nodiscard]] std::expected<void, engine_error>
  operator()(const request::create_order &);

  [[nodiscard]] std::expected<void, engine_error>
  operator()(const request::snapshot &);

  [[nodiscard]] std::expected<void, engine_error>
  operator()(const std::monostate &) {
    return std::unexpected{engine_error::invalid_request};
  }

  constexpr auto &registry() noexcept { return books_; }

  void restore() { load_engine_registry(books_, snapshot_file_); }

private:
  matcher::book_registry books_;
  // TODO: support timestamped filenames so as
  //       to not overwrite old snapshots.
  std::string snapshot_file_;
  std::future<void> snapshot_future_;
};

} // namespace matcher

#endif
