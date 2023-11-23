#include <algorithm>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "book/book.hpp"

/// Return order_ids in book, in the order in which they appear.
auto get_book_order_ids(matcher::book::book &book, types::side side) {
  std::vector<types::order_id> ids{};
  for (auto order_it = book.begin(side); order_it != book.end(side);
       ++order_it) {
    ids.push_back(order_it->order_id);
  }
  return ids;
}

void insert_orders(matcher::book::book &book,
                   std::vector<types::order> &orders) {
  std::ranges::for_each(
      orders, [&](auto order) { book.insert_order(std::move(order)); });
}

TEST_CASE("Insert buy orders") {
  std::vector<types::order> orders{
      {1, 2, 3, types::side::buy},
      // Best price
      {2, 3, 3, types::side::buy},
      // Same price as 1 but lower time priority
      {3, 2, 3, types::side::buy},
      // Worst price
      {4, 1, 3, types::side::buy},
  };
  std::vector<types::order_id> expected_buy_ids{2, 1, 3, 4};

  matcher::book::book book{1};
  insert_orders(book, orders);

  auto buy_ids = get_book_order_ids(book, types::side::buy);
  REQUIRE(buy_ids == expected_buy_ids);
}

TEST_CASE("Insert sell orders") {
  std::vector<types::order> orders{
      {1, 2, 3, types::side::sell},
      // Worst price
      {2, 3, 3, types::side::sell},
      // Same price as 1 but lower time priority
      {3, 2, 3, types::side::sell},
      // Best price
      {4, 1, 3, types::side::sell},
  };
  std::vector<types::order_id> expected_ids{4, 1, 3, 2};

  matcher::book::book book{1};
  insert_orders(book, orders);

  auto ids = get_book_order_ids(book, types::side::sell);
  REQUIRE(ids == expected_ids);
}
