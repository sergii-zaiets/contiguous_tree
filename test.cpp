#include <iostream>
#include "gtest/gtest.h"
#include "contiguous_tree.h"

using namespace contiguous;

TEST(Test, empty_tree) {
  Tree<int> tree;
  EXPECT_TRUE(tree.empty());
}

TEST(Test1, add_top) {
  Tree<int> tree;
  auto top = tree.create_top(5);
  EXPECT_EQ(5, top->data());
}

TEST(Test2, test_3) {
  Tree<int> tree;
  auto top = tree.create_top(5);
  auto child = tree.add_child(top, 8);
  EXPECT_EQ(8, child->data());
}

TEST(Test3, test_4) {
  EXPECT_TRUE(true);
}

TEST(Test4, test_5) {
  EXPECT_TRUE(true);
}
