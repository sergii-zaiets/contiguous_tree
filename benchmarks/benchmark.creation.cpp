#include "utils.h"
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

// TODO: function to calculate tree size

// Define another benchmark
static void bm_create_classical_tree_in_depth(benchmark::State &state) {
  int depth = state.range(0);
  int width = state.range(1);
  for (auto _ : state) {
    int i = 0;
    Tree<int> tree =
        create_tree_in_depth<int>(depth, width, [&]() { return ++i; });
    ASSERT_FALSE(tree.empty());
  }
}
BENCHMARK(bm_create_classical_tree_in_depth)
    ->Unit(benchmark::kMillisecond)
    ->Args({10, 2})
    ->Args({11, 2})
    ->Args({12, 2})
    ->Args({13, 3})
    ->Args({13, 4});

// Define another benchmark
static void bm_create_contiguous_tree_in_depth(benchmark::State &state) {
  int depth = state.range(0);
  int width = state.range(1);
  for (auto _ : state) {
    int i = 0;
    contiguous::Tree<int> tree = create_contiguous_tree_in_depth<int>(
        depth, width, [&]() { return ++i; });
    ASSERT_FALSE(tree.empty());
  }
}
BENCHMARK(bm_create_contiguous_tree_in_depth)
    ->Unit(benchmark::kMillisecond)
    ->Args({10, 2})
    ->Args({11, 2})
    ->Args({12, 2})
    ->Args({13, 3})
    ->Args({13, 4});

// Define another benchmark
static void bm_create_classical_tree_in_width(benchmark::State &state) {
  int depth = state.range(0);
  int width = state.range(1);
  for (auto _ : state) {
    int i = 0;
    Tree<int> tree =
        create_tree_in_width<int>(depth, width, [&]() { return ++i; });
    ASSERT_FALSE(tree.empty());
  }
}
BENCHMARK(bm_create_classical_tree_in_width)
    ->Unit(benchmark::kMillisecond)
    ->Args({10, 2})
    ->Args({11, 2})
    ->Args({12, 2})
    ->Args({13, 3})
    ->Args({13, 4});

// Define another benchmark
static void bm_create_contiguous_tree_in_width(benchmark::State &state) {
  int depth = state.range(0);
  int width = state.range(1);
  for (auto _ : state) {
    int i = 0;
    contiguous::Tree<int> tree = create_contiguous_tree_in_width<int>(
        depth, width, [&]() { return ++i; });
    ASSERT_FALSE(tree.empty());
  }
}
BENCHMARK(bm_create_contiguous_tree_in_width)
    ->Unit(benchmark::kMillisecond)
    ->Args({10, 2})
    ->Args({11, 2})
    ->Args({12, 2})
    ->Args({13, 3})
    ->Args({13, 4});