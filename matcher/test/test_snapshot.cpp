#include <print>
#include <ranges>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

#include <book_registry.hpp>
#include <engine.hpp>

#include "generators.hpp"

import matcher.types;

auto save_and_restore(matcher::book_registry &registry,
                      std::string_view filename) {
  matcher::save_engine_registry(registry, filename);
  matcher::book_registry restored_registry{};
  matcher::load_engine_registry(restored_registry, filename);
  return restored_registry;
}

auto insert_orders(matcher::book::book &book, std::span<types::order> orders) {
  for (auto order : orders) {
    book.insert_order(std::move(order));
  }
}

auto create_books(matcher::book_registry &registry, int num_books) {
  std::vector<matcher::book::book *> v{};
  v.reserve(num_books);

  std::ranges::generate_n(std::back_inserter(v), num_books, [&, id{0}] mutable {
    registry.create_book(id);
    return &registry.get_book(id++);
  });
  return v;
}

TEST_CASE("Test book registry serialization and deserialization") {
  constexpr std::string_view filename = "output.xml";

  constexpr int num_books = 5;
  constexpr int num_orders = 5;
  matcher::book_registry registry{};

  {
    auto books = create_books(registry, num_books);
    for (auto book : books) {
      auto orders =
          GENERATE_COPY(take(1, chunk(num_orders, generators::random_order())));
      insert_orders(*book, orders);
    }
  }

  {
    auto restored_registry = save_and_restore(registry, filename);
    for (auto i : std::views::iota(0, num_books)) {
      REQUIRE(restored_registry.get_book(i) == registry.get_book(i));
    }
  }
}
