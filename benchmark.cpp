#include <iostream>
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
#include "contiguous_tree.h"
#include "tree.h"

static void StringCreation(benchmark::State &state)
{
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(StringCreation);

// Define another benchmark
static void StringCopy(benchmark::State &state)
{
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
BENCHMARK(StringCopy);

template <class T>
void add(Node<T> &node, int depth, int width)
{
  // std::cout << "depth=" << depth << std::endl;

  if (depth <= 0)
    return;

  int i = width;
  node.children_.reserve(width);
  while (i--)
  {
    node.children_.emplace_back(std::make_unique<Node<T>>(1));
    add(*node.children_.back(), --depth, width);
  }
}

template <class T>
Tree<T> create_classical_tree(int depth, int width)
{
  if (depth <= 0)
    return Tree<T>();

  Tree<T> tree(1);
  add(tree.root(), --depth, width);
  return tree;
}

// Define another benchmark
static void create_classical_tree(benchmark::State &state)
{
  int depth = state.range(0);
  int width = state.range(0);
  for (auto _ : state)
  {
    Tree<int> tree = create_classical_tree<int>(depth, width);
    ASSERT_FALSE(tree.is_empty());
  }
}
BENCHMARK(create_classical_tree)->Arg(8)->Arg(16)->Arg(32)->Arg(64);