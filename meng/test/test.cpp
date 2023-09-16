#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "ring_buffer.hpp"

// TEST_CASE("Basic ring buffer test") {
//   const auto buf_size = 5;
//   meng::ring_buffer<int, buf_size> buf;
//   auto prod_cursor = std::make_shared<meng::cursor>();
//   auto cons_cursor = std::make_shared<meng::cursor>();
//   meng::producer prod{cons_cursor, prod_cursor, buf};
//   meng::consumer cons{cons_cursor, prod_cursor, buf};
//
//   auto thread1 = std::thread([&]() {
//     // sleep to catch case of consumer reading immediately
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     prod.produce_one(buf, 1);
//     prod.produce_one(buf, 2);
//     prod.commit();
//   });
//
//   auto thread2 = std::thread([&]() {
//     REQUIRE(cons.consume_one(buf) == 1);
//     REQUIRE(cons.consume_one(buf) == 2);
//   });
//
//   thread1.join();
//   thread2.join();
// }

TEST_CASE("Batch iterator") {
  const auto buf_size = 5;
  const auto batch_size = 2;
  const auto num_items = 101;
  meng::ring_buffer<int, buf_size> buf;
  auto prod_cursor = std::make_shared<meng::cursor>();
  auto cons_cursor = std::make_shared<meng::cursor>();
  meng::producer prod{buf, cons_cursor, prod_cursor};

  auto thread1 = std::thread([&]() {
    for (int i = 0; i < num_items; i++) {
      prod.produce_one(i);
      if (i % batch_size == 0) {
        prod.commit();
      }
    }
  });

  auto thread2 = std::thread([&]() {
    auto i = 0;
    for (auto val : meng::batch_iterate<decltype(buf)>(buf, cons_cursor, prod_cursor, 32)) {
      REQUIRE(val == i);
      ++i;
      if (val == num_items - 1) return;
    }
  });

  thread1.join();
  thread2.join();
}
