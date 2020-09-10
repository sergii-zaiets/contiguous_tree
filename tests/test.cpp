#include "contiguous_tree.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace contiguous;

TEST(Test, empty_tree) {
  Tree<int> tree;
  EXPECT_TRUE(tree.empty());
}

TEST(Test1, add_top) {
  Tree<int> tree(5);
  auto root = tree.root();
  EXPECT_EQ(5, root->data());
}

TEST(Test2, test_3) {
  Tree<int> tree(5);
  auto root = tree.root();
  auto child = root.add_child(8);
  EXPECT_EQ(8, child->data());
}

TEST(Test3, test_4) { EXPECT_TRUE(true); }

TEST(Test4, test_5) { EXPECT_TRUE(true); }
