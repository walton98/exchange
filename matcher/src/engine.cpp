#include "engine.hpp"

namespace matcher {

engine::~engine() {
  // wait for any writer threads to complete
  if (snapshot_future_.valid()) {
    snapshot_future_.wait();
  }
}

std::expected<void, engine_error>
engine::operator()(const request::create_book &request) {
  books_.create_book(request.id());
  std::cout << "creating book" << std::endl;
  return {};
}

std::expected<void, engine_error>
engine::operator()(const request::create_order &request) {
  auto &book = books_.get_book(request.book_id());
  book.insert_order(request.order());
  std::cout << "creating order" << std::endl;
  return {};
}

std::expected<void, engine_error>
engine::operator()(const request::snapshot &request) {
  using namespace std::chrono_literals;

  if (snapshot_future_.valid() &&
      snapshot_future_.wait_for(0ms) != std::future_status::ready) {
    std::cout << "skipping snapshot" << std::endl;
    return std::unexpected{engine_error::snapshot_in_progress};
  }

  std::cout << "snapshotting" << std::endl;
  // copy registry in memory to another thread,
  // and write to disk in thread.
  auto writer_fn = [fn = snapshot_file_, reg = books_]() {
    save_engine_registry(reg, fn);
  };
  snapshot_future_ = std::async(std::launch::async, writer_fn);

  return {};
}

} // namespace matcher
