#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "ring_buffer.hpp"

TEST_CASE("Batch iterator") {
  const auto buf_size = 1024;
  const auto batch_size = 32;
  const auto num_items = 1'000'000;
  meng::ring_buffer<int, buf_size> buf;
  meng::cursor_pair cursors{};
  meng::producer prod{buf, cursors.prod_cursor};

  auto thread1 = std::thread([&]() {
    for (int i = 0; i < num_items; i++) {
      prod.produce_one(i);
      if (i % batch_size == 0) {
        prod.commit();
      }
    }
    prod.commit();
  });

  auto thread2 = std::thread([&]() {
    auto i = 0;
    for (auto val : meng::batch_iterate(buf, cursors.cons_cursor, batch_size)) {
      REQUIRE(val == i);
      ++i;
      if (val == num_items - 1) return;
    }
  });

  thread1.join();
  thread2.join();
  cursors.unlink();
}
