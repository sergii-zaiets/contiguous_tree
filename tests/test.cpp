#include "contiguous_tree.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(Contiguous_test, empty_tree) {
  contiguous::Tree<int> tree;
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(0, tree.size());
  EXPECT_FALSE(tree.root());
  tree.for_each([](auto &n) {
    ASSERT_TRUE(false); // must not be called
  });
}

TEST(Test1, only_root) {
  contiguous::Tree<int> tree(5);
  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(1, tree.size());
  EXPECT_TRUE(tree.root());
  EXPECT_EQ(5, tree.root()->data());

  std::vector<int> collect;
  tree.for_each([&](auto &n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({5}), collect);

  auto root_child = ++tree.root();
  EXPECT_FALSE(root_child);
}

TEST(Test2, test_3) {
  contiguous::Tree<int> tree(5);
  auto root = tree.root();
  auto child = root.add_child(8);
  EXPECT_EQ(8, child->data());
}
