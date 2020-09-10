#include "contiguous_tree.h"
#include "tree.h"

/*
 *
 ******************************************************************************/
template <class T, class Function>
void add_to_tree_in_depth(Node<T> &node, int depth, int width,
                          Function const &function) {
  if (depth <= 0)
    return;

  int i = width;
  while (i--) {
    node.children.emplace_back(function());
    add_to_tree_in_depth(node.children.back(), depth - 1, width, function);
  }
}

template <class T, class Function>
Tree<T> create_tree_in_depth(int depth, int width, Function const &function) {
  if (depth <= 0 || width <= 0)
    return Tree<T>();

  Tree<T> tree(function());
  add_to_tree_in_depth(tree.root(), --depth, width, function);
  return tree;
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void add_to_contiguous_tree_in_depth(
    typename contiguous::Tree<T>::Node_ptr node, int depth, int width,
    Function const &function) {
  if (depth <= 0)
    return;

  int i = width;
  while (i--) {
    auto child = node.add_child(function());
    add_to_contiguous_tree_in_depth<T>(child, depth - 1, width, function);
  }
}

template <class T, class Function>
contiguous::Tree<T> create_contiguous_tree_in_depth(int depth, int width,
                                                    Function const &function) {
  if (depth <= 0 || width <= 0)
    return contiguous::Tree<T>();

  contiguous::Tree<T> tree(function());
  add_to_contiguous_tree_in_depth<T>(tree.root(), --depth, width, function);
  return tree;
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void add_to_contiguous_tree_in_width(
    typename contiguous::Tree<T>::Node_ptr node, int depth, int width,
    Function const &function) {
  if (depth <= 0)
    return;

  int i = width;
  while (i--) {
    auto child = node.add_child(function());
  }

  for (auto c = node.children_begin(); !!c; c = c.next_child()) {
    add_to_contiguous_tree_in_width<T>(c, depth - 1, width, function);
  }
}

template <class T, class Function>
contiguous::Tree<T> create_contiguous_tree_in_width(int depth, int width,
                                                    Function const &function) {
  if (depth <= 0 || width <= 0)
    return contiguous::Tree<T>();

  contiguous::Tree<T> tree(function());
  add_to_contiguous_tree_in_width<T>(tree.root(), --depth, width, function);
  return tree;
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void iterate_in_depth(Node<T> &node, Function const &function) {
  function(node.data);

  for (auto &c : node.children) {
    iterate_in_depth<T>(c, function);
  }
}

template <class T, class Function>
void iterate_in_depth(Tree<T> &tree, Function const &function) {
  if (tree.empty())
    return;
  iterate_in_depth<T>(tree.root(), function);
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void iterate_in_depth(typename contiguous::Tree<T>::Node_ptr node,
                      Function const &function) {
  if (!node)
    return;
  function(node->data());

  for (auto c = node.children_begin(); !!c; c = c.next_child()) {
    iterate_in_depth<T>(c, function);
  }
}

template <class T, class Function>
void iterate_in_depth(contiguous::Tree<T> &tree, Function const &function) {
  iterate_in_depth<T>(tree.root(), function);
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void iterate_in_width(typename contiguous::Tree<T>::Node_ptr node,
                      Function const &function) {
  if (!node)
    return;

  for (auto c = node.children_begin(); !!c; c = c.next_child()) {
    function(c->data());
  }

  for (auto c = node.children_begin(); !!c; c = c.next_child()) {
    iterate_in_width<T>(c, function);
  }
}

template <class T, class Function>
void iterate_in_width(contiguous::Tree<T> &tree, Function const &function) {
  auto root = tree.root();
  if (root)
    function(root->data());
  iterate_in_width<T>(root, function);
}