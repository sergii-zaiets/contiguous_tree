#include "utils.h"
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

class Traverse_classical_tree : public benchmark::Fixture {
public:
  Tree<int> tree_;

  void SetUp(const ::benchmark::State &state) {
    auto s = state; // get rif of this
    int depth = state.range(0);
    int width = state.range(1);
    for (auto _ : s) {
      tree_ = create_tree_in_depth<int>(depth, width, []() { return 1; });
    }
    ASSERT_FALSE(tree_.empty());
  }

  void TearDown(const ::benchmark::State &state) {}
};

BENCHMARK_DEFINE_F(Traverse_classical_tree, in_depth_and_sumup)
(benchmark::State &state) {
  for (auto _ : state) {
    int sum = 0;
    iterate_in_depth(tree_, [&](int &n) { sum += n; });
    ASSERT_TRUE(sum > 0);
  }
}

// Define another benchmark
BENCHMARK_REGISTER_F(Traverse_classical_tree, in_depth_and_sumup)
    ->Unit(benchmark::kMillisecond)
    ->Args({10, 2})
    ->Args({11, 2})
    ->Args({12, 2})
    ->Args({13, 3})
    ->Args({13, 4})
    ->Args({27, 2});

/*
 *
 ******************************************************************************/
class Traverse_contiguous_tree : public benchmark::Fixture {
public:
  contiguous::Tree<int> tree_;

  void SetUp(const ::benchmark::State &state) {
    auto s = state; // get rif of this
    int depth = state.range(0);
    int width = state.range(1);
    for (auto _ : s) {
      tree_ = create_contiguous_tree_in_depth<int>(depth, width,
                                                   []() { return 1; });
    }
    ASSERT_FALSE(tree_.empty());
  }

  void TearDown(const ::benchmark::State &state) {}
};

BENCHMARK_DEFINE_F(Traverse_contiguous_tree, in_depth_and_sumup)
(benchmark::State &state) {
  for (auto _ : state) {
    int sum = 0;
    iterate_in_depth(tree_, [&](int &n) { sum += n; });
    ASSERT_TRUE(sum > 0);
  }
}

// Define another benchmark
BENCHMARK_REGISTER_F(Traverse_contiguous_tree, in_depth_and_sumup)
    ->Unit(benchmark::kMillisecond)
    ->Args({10, 2})
    ->Args({11, 2})
    ->Args({12, 2})
    ->Args({13, 3})
    ->Args({13, 4})
    ->Args({27, 2});
