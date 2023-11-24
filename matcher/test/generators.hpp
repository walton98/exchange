#ifndef MATCHER_TEST_GENERATORS_HPP
#define MATCHER_TEST_GENERATORS_HPP

#include <random>

#include <catch2/generators/catch_generators.hpp>

#include <types.hpp>

namespace generators {

static constexpr unsigned int max_quantity{1'000'000};
static constexpr types::price max_price{10000};

class RandomOrderGenerator : public Catch::Generators::IGenerator<types::order> {
public:
  RandomOrderGenerator()
      : rand_{std::random_device{}()}, order_id_{},
        price_dist_{0, max_price}, quantity_dist_{0, max_quantity}, side_dist_{0, 1}, current_order_{} {
    static_cast<void>(next());
  }

  const types::order &get() const override { return current_order_; }

  bool next() override {
    auto quantity = quantity_dist_(rand_);
    auto price = price_dist_(rand_);
    auto side = static_cast<types::side>(side_dist_(rand_));
    current_order_ = types::order{order_id_, price, quantity, side};
    ++order_id_;
    return true;
  }

private:
  std::minstd_rand rand_;
  types::order_id order_id_;
  std::uniform_int_distribution<types::price> price_dist_;
  std::uniform_int_distribution<types::quantity> quantity_dist_;
  std::uniform_int_distribution<size_t> side_dist_;
  types::order current_order_;
};

inline auto random_order() {
  return Catch::Generators::GeneratorWrapper<types::order>(
      Catch::Detail::make_unique<RandomOrderGenerator>());
}

} // namespace generators

#endif
