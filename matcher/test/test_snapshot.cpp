#include <ranges>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

#include <book_registry.hpp>
#include <engine.hpp>
#include <snapshot.hpp>
#include <types.hpp>

#include "generators.hpp"

auto save_and_restore(matcher::engine &engine, std::string_view filename) {
  engine.save();
  matcher::engine reloaded_engine{filename};
  reloaded_engine.restore();
  return reloaded_engine;
}

auto insert_orders(matcher::book::book &book, std::span<types::order> orders) {
  for (auto order : orders) {
    book.insert_order(std::move(order));
  }
}

auto create_books(matcher::book_registry &registry, int num_books) {
  std::vector<matcher::book::book *> v{};
  std::cout << v.capacity() << std::endl;
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
  matcher::engine engine{filename};

  {
    auto books = create_books(engine.registry(), num_books);
    for (auto book : books) {
      auto orders =
          GENERATE_COPY(take(1, chunk(num_orders, generators::random_order())));
      insert_orders(*book, orders);
    }
  }

  {
    auto reloaded_engine = save_and_restore(engine, filename);
    for (auto i : std::views::iota(0, num_books)) {
      REQUIRE(reloaded_engine.registry().get_book(i) ==
              engine.registry().get_book(i));
    }
  }
}
