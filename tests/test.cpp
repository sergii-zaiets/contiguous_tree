#include "contiguous_tree.h"
#include "utils.h"
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

TEST(Contiguous_test, only_root) {
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

TEST(Contiguous_test, root_with_2_children) {
  contiguous::Tree<int> tree(5);

  auto root = tree.root();
  auto c1 = root.add_child(8);
  auto c2 = root.add_child(10);

  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(3, tree.size());

  EXPECT_EQ(5, root->data());
  EXPECT_EQ(8, c1->data());
  EXPECT_EQ(10, c2->data());

  std::vector<int> collect;
  tree.for_each([&](auto &n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({5, 8, 10}), collect);

  auto c = root.children_begin();
  ASSERT_TRUE(c);
  EXPECT_EQ(8, c->data());
  ASSERT_FALSE(c.children_begin());
  ++c;
  ASSERT_TRUE(c);
  EXPECT_EQ(10, c->data());
  ASSERT_FALSE(c.children_begin());
  ++c;
  ASSERT_FALSE(c);
}

TEST(Contiguous_test, test_for_each___create_in_depth_with_d_3_w_2) {
  int depth = 3;
  int width = 2;
  contiguous::Tree<int> tree =
      create_contiguous_tree_in_depth<int>(depth, width, []() {
        static int i = 0;
        return ++i;
      });

  std::vector<int> collect;
  tree.for_each([&](auto &n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7}), collect);
}

TEST(Contiguous_test, iterate_in_depth___create_in_depth_with_d_3_w_2) {
  int depth = 3;
  int width = 2;
  contiguous::Tree<int> tree =
      create_contiguous_tree_in_depth<int>(depth, width, []() {
        static int i = 0;
        return ++i;
      });

  std::vector<int> collect;
  iterate_in_depth(tree, [&](int &n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7}), collect);
}

TEST(Contiguous_test, iterate_in_width___create_in_depth_with_d_3_w_2) {
  int depth = 3;
  int width = 2;
  contiguous::Tree<int> tree =
      create_contiguous_tree_in_depth<int>(depth, width, []() {
        static int i = 0;
        return ++i;
      });

  std::vector<int> collect;
  iterate_in_width(tree, [&](int &n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 5, 3, 4, 6, 7}), collect);
}

TEST(Contiguous_test, test_for_each___create_in_width_with_d_3_w_2) {
  int depth = 3;
  int width = 2;
  contiguous::Tree<int> tree =
      create_contiguous_tree_in_width<int>(depth, width, []() {
        static int i = 0;
        return ++i;
      });

  std::vector<int> collect;
  tree.for_each([&](auto &n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7}), collect);
}

TEST(Contiguous_test, iterate_in_depth___create_in_width_with_d_3_w_2) {
  int depth = 3;
  int width = 2;
  contiguous::Tree<int> tree =
      create_contiguous_tree_in_width<int>(depth, width, []() {
        static int i = 0;
        return ++i;
      });

  std::vector<int> collect;
  iterate_in_depth(tree, [&](int &n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 4, 5, 3, 6, 7}), collect);
}

TEST(Contiguous_test, iterate_in_width___create_in_width_with_d_3_w_2) {
  int depth = 3;
  int width = 2;
  contiguous::Tree<int> tree =
      create_contiguous_tree_in_width<int>(depth, width, []() {
        static int i = 0;
        return ++i;
      });

  std::vector<int> collect;
  iterate_in_width(tree, [&](int &n) { collect.emplace_back(n); });
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7}), collect);
}