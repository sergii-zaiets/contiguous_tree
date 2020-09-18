#include "tree.h"
#include "utils.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(Classical_tree, empty_tree) {
  {
    Tree<int> tree;
    EXPECT_TRUE(tree.empty());
  }
  {
    Tree<int> tree = create_tree_in_depth<int>(0, 1, []() { return 0; });
    EXPECT_TRUE(tree.empty());
  }
  {
    Tree<int> tree = create_tree_in_width<int>(0, 1, []() { return 0; });
    EXPECT_TRUE(tree.empty());
  }
  {
    Tree<int> tree = create_tree_in_depth<int>(1, 0, []() { return 0; });
    EXPECT_TRUE(tree.empty());
  }
  {
    Tree<int> tree = create_tree_in_width<int>(1, 0, []() { return 0; });
    EXPECT_TRUE(tree.empty());
  }
  {
    Tree<int> tree;
    iterate_in_depth(tree, [](int n) {});
    iterate_in_width(tree, [](int n) {});
  }
}

TEST(Classical_tree, only_root) {
  Tree<int> tree(5);
  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(5, tree.root().data);
}

TEST(Classical_tree, iterate_in_depth___create_in_depth_with_d_3_w_2) {
  int depth = 3;
  int width = 2;

  int i = 0;
  Tree<int> tree =
      create_tree_in_depth<int>(depth, width, [&]() { return ++i; });

  std::vector<int> collect;
  iterate_in_depth(tree, [&](int n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7}), collect);
}

TEST(Classical_tree, iterate_in_width___create_in_depth_with_d_3_w_2) {
  int depth = 3;
  int width = 2;

  int i = 0;
  Tree<int> tree =
      create_tree_in_depth<int>(depth, width, [&]() { return ++i; });

  std::vector<int> collect;
  iterate_in_width(tree, [&](int n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 5, 3, 4, 6, 7}), collect);
}

TEST(Classical_tree, iterate_in_depth___create_in_width_with_d_3_w_2) {
  int depth = 3;
  int width = 2;

  int i = 0;
  Tree<int> tree =
      create_tree_in_width<int>(depth, width, [&]() { return ++i; });

  std::vector<int> collect;
  iterate_in_depth(tree, [&](int n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 4, 5, 3, 6, 7}), collect);
}

TEST(Classical_tree, iterate_in_width___create_in_width_with_d_3_w_2) {
  int depth = 3;
  int width = 2;

  int i = 0;
  Tree<int> tree =
      create_tree_in_width<int>(depth, width, [&]() { return ++i; });

  std::vector<int> collect;
  iterate_in_width(tree, [&](int n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7}), collect);
}

TEST(Classical_tree, iterate_in_depth___create_in_depth_with_d_4_w_2) {
  int depth = 4;
  int width = 2;

  int i = 0;
  Tree<int> tree =
      create_tree_in_depth<int>(depth, width, [&]() { return ++i; });

  std::vector<int> collect;
  iterate_in_depth(tree, [&](int n) { collect.emplace_back(n); });
  EXPECT_EQ(
      std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}),
      collect);
}

TEST(Classical_tree, iterate_in_width___create_in_depth_with_d_4_w_2) {
  int depth = 4;
  int width = 2;

  int i = 0;
  Tree<int> tree =
      create_tree_in_depth<int>(depth, width, [&]() { return ++i; });

  std::vector<int> collect;
  iterate_in_width(tree, [&](int n) { collect.emplace_back(n); });
  EXPECT_EQ(
      std::vector<int>({1, 2, 9, 3, 6, 10, 13, 4, 5, 7, 8, 11, 12, 14, 15}),
      collect);
}

TEST(Classical_tree, iterate_in_depth___create_in_width_with_d_4_w_2) {
  int depth = 4;
  int width = 2;

  int i = 0;
  Tree<int> tree =
      create_tree_in_width<int>(depth, width, [&]() { return ++i; });

  std::vector<int> collect;
  iterate_in_depth(tree, [&](int n) { collect.emplace_back(n); });
  EXPECT_EQ(
      std::vector<int>({1, 2, 4, 8, 9, 5, 10, 11, 3, 6, 12, 13, 7, 14, 15}),
      collect);
}

TEST(Classical_tree, iterate_in_width___create_in_width_with_d_4_w_2) {
  int depth = 4;
  int width = 2;

  int i = 0;
  Tree<int> tree =
      create_tree_in_width<int>(depth, width, [&]() { return ++i; });

  std::vector<int> collect;
  iterate_in_width(tree, [&](int n) { collect.emplace_back(n); });
  EXPECT_EQ(
      std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}),
      collect);
}
