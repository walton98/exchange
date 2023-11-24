#ifndef MATCHER_ENGINE_HPP
#define MATCHER_ENGINE_HPP

#include <expected>
#include <fstream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <matcher.pb.h>

#include "book_registry.hpp"
#include "request.hpp"

namespace matcher {

enum engine_error {
  already_exists,
  invalid_request,
};

class engine {
public:
  engine() : books_{} {}

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

  void restore() {
    if (!std::filesystem::exists(snapshot_file_)) {
      std::cout << "missing state file" << std::endl;
      return;
    }

    auto ifs = std::ifstream(snapshot_file_.c_str());
    boost::archive::xml_iarchive ia(ifs);

    ia >> boost::serialization::make_nvp("state", *this);
  }

  void save() const {
    auto ofs = std::ofstream(snapshot_file_.c_str());
    boost::archive::xml_oarchive oa(ofs);
    oa << boost::serialization::make_nvp("state", *this);
  }

  template <typename Archive>
  void serialize(Archive &ar, unsigned int const /*version*/) {
    ar &boost::serialization::make_nvp("registry", books_);
  }

private:
  matcher::book_registry books_;
  std::string snapshot_file_;
};

} // namespace matcher

#endif
