#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "book.hpp"

TEST_CASE("Insert order") {
  std::vector<matcher::order> orders{
      {1, 2, 3},
      {2, 3, 3},
      {3, 1, 3},
  };
  matcher::book book{1};
  for (auto order : orders) {
    book.insert_order(std::move(order));
  }

  std::vector<types::order_id_t> actual_ids{};
  for (auto order_it = book.begin(types::side::buy);
       order_it != book.end(types::side::buy); ++order_it) {
    actual_ids.push_back(order_it->id);
  }
  REQUIRE(actual_ids == std::vector<types::order_id_t>{2, 1, 3});
}
