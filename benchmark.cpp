#include <iostream>
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
#include "contiguous_tree.h"
#include "tree.h"

template <class T>
void add(Node<T> &node, int depth, int width)
{
  if (depth <= 0)
    return;

  int i = width;
  while (i--)
  {
    node.children_.emplace_back(1);
    add(node.children_.back(), depth - 1, width);
  }
}

template <class T>
Tree<T> create_classical_tree(int depth, int width)
{
  if (depth <= 0 || width <= 0)
    return Tree<T>();

  Tree<T> tree(1);
  add(tree.root(), --depth, width);
  return tree;
}

template <class T>
void add(contiguous::Tree<T> &tree, typename contiguous::Tree<T>::Node_ptr node, int depth, int width)
{
  if (depth <= 0)
    return;

  int i = width;
  while (i--)
  {
    auto child = tree.add_child(node, 1);
    add(tree, child, depth - 1, width);
  }
}

template <class T>
contiguous::Tree<T> create_contiguous_tree(int depth, int width)
{
  if (depth <= 0 || width <= 0)
    return contiguous::Tree<T>();

  contiguous::Tree<T> tree;
  auto root = tree.create_top(1);
  add(tree, root, --depth, width);
  return tree;
}

// TODO: function to calculate tree size

// Define another benchmark
static void bm_create_classical_tree(benchmark::State &state)
{
  int depth = state.range(0);
  int width = state.range(1);
  for (auto _ : state)
  {
    Tree<int> tree = create_classical_tree<int>(depth, width);
    ASSERT_FALSE(tree.empty());
  }
}
BENCHMARK(bm_create_classical_tree)->Unit(benchmark::kMillisecond)->Args({10, 2})->Args({11, 2})->Args({12, 2})->Args({13, 3})->Args({13, 4})->Args({27, 2});

// Define another benchmark
static void bm_create_contiguous_tree(benchmark::State &state)
{
  int depth = state.range(0);
  int width = state.range(1);
  for (auto _ : state)
  {
    contiguous::Tree<int> tree = create_contiguous_tree<int>(depth, width);
    ASSERT_FALSE(tree.empty());
  }
}
BENCHMARK(bm_create_contiguous_tree)->Unit(benchmark::kMillisecond)->Args({10, 2})->Args({11, 2})->Args({12, 2})->Args({13, 3})->Args({13, 4})->Args({27, 2});
