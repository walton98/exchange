#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "ring_buffer/ring_buffer.hpp"

TEST_CASE("Batch iterator") {
  const auto buf_size = 512;
  const auto batch_size = buf_size / GENERATE(1, 2, 4, 16);
  const auto num_items = GENERATE(10, 1'000, 1'000'000);

  ring_buffer::ring_buffer<int, buf_size> buf;
  ring_buffer::cursor_pair cursors{};
  ring_buffer::producer prod{buf, cursors.prod_cursor};

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
    auto batch_iterator =
        ring_buffer::batch_iterate(buf, cursors.cons_cursor, batch_size);
    for (auto batch : batch_iterator) {
      for (auto val : batch) {
        REQUIRE(val == i);
        ++i;
        if (val == num_items - 1)
          return;
      }
    }
  });

  thread1.join();
  thread2.join();
  cursors.unlink();
}
