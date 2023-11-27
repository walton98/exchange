#include "spdlog/spdlog.h"

#include "engine.hpp"

namespace matcher {

inline void save_engine_registry(const book_registry &registry,
                                 std::string_view filename) {
  auto ofs = std::ofstream(filename);
  boost::archive::xml_oarchive oa(ofs);
  oa << BOOST_SERIALIZATION_NVP(registry);
}

inline void load_engine_registry(book_registry &registry,
                                 std::string_view filename) {
  if (!std::filesystem::exists(filename)) {
    spdlog::info("Missing state file");
    return;
  }

  spdlog::info("Restoring from state file");
  auto ifs = std::ifstream(filename);
  boost::archive::xml_iarchive ia(ifs);
  ia >> BOOST_SERIALIZATION_NVP(registry);
}

engine::~engine() {
  // wait for any writer threads to complete
  if (snapshot_future_.valid()) {
    snapshot_future_.wait();
  }
}

std::expected<void, engine_error>
engine::operator()(const request::create_book &request) {
  auto inserted = registry_.create_book(request.id());
  if (inserted) {
    spdlog::info("Created book {}", request.id());
    return {};
  } else {
    spdlog::info("Book {} already exists", request.id());
    return std::unexpected{engine_error::already_exists};
  }
}

std::expected<void, engine_error>
engine::operator()(const request::create_order &request) {
  // TODO: check order id doesn't already exist
  //       may need list of order ids in whole registry?
  auto &book = registry_.get_book(request.book_id());
  book.insert_order(request.order());
  spdlog::info("Created order {}", request.order().order_id);
  return {};
}

std::expected<void, engine_error>
engine::operator()(const request::snapshot &request) {
  using namespace std::chrono_literals;

  if (snapshot_future_.valid() &&
      snapshot_future_.wait_for(0ms) != std::future_status::ready) {
    spdlog::warn("Skipping snapshot creation");
    return std::unexpected{engine_error::snapshot_in_progress};
  }

  spdlog::info("Creating snapshot...");
  // copy registry in memory to another thread,
  // and write to disk in thread.
  auto writer_fn = [fn = snapshot_file_, reg = registry_]() {
    save_engine_registry(reg, fn);
    spdlog::info("Finished writing snapshot");
  };
  snapshot_future_ = std::async(std::launch::async, writer_fn);

  return {};
}

void engine::restore() { load_engine_registry(registry_, snapshot_file_); }

} // namespace matcher
