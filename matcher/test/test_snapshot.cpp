#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include <snapshot.hpp>
#include <types.hpp>

TEST_CASE("Test serialization and deserialization") {
  const std::string s = "output.xml";
  types::order order{1, 2, 3, types::side::sell};
  write_to_file(s, order);
  auto parsed = read_from_file<types::order>(s);
  REQUIRE(parsed.order_id == order.order_id);
  REQUIRE(parsed.price == order.price);
  REQUIRE(parsed.quantity == order.quantity);
  REQUIRE(parsed.side == order.side);
}
