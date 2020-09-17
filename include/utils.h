#include "contiguous_tree.h"
#include "tree.h"

/*
 * Create a classical tree in depth
 ******************************************************************************/
template <class T, class Function>
void add_to_tree_in_depth(Node<T> &node, int depth, int width,
                          Function const &function) {
  if (depth <= 0) {
    return;
  }

  int i = width;
  while (i--) {
    node.children.emplace_back(function());
    add_to_tree_in_depth(node.children.back(), depth - 1, width, function);
  }
}

template <class T, class Function>
Tree<T> create_tree_in_depth(int depth, int width, Function const &function) {
  if (depth <= 0 || width <= 0) {
    return Tree<T>();
  }

  Tree<T> tree(function());
  add_to_tree_in_depth<T>(tree.root(), --depth, width, function);
  return tree;
}

/*
 * Create a contiguous tree in depth
 ******************************************************************************/
template <class T, class Function>
void add_to_contiguous_tree_in_depth(
    typename contiguous::Tree<T>::Node_ptr node, int depth, int width,
    Function const &function) {
  if (depth <= 0) {
    return;
  }

  int i = width;
  while (i--) {
    auto child = node.add_child(function());
    add_to_contiguous_tree_in_depth<T>(child, depth - 1, width, function);
  }
}

template <class T, class Function>
contiguous::Tree<T> create_contiguous_tree_in_depth(int depth, int width,
                                                    Function const &function) {
  if (depth <= 0 || width <= 0) {
    return contiguous::Tree<T>();
  }

  contiguous::Tree<T> tree(function());
  add_to_contiguous_tree_in_depth<T>(tree.root(), --depth, width, function);
  return tree;
}

/*
 * Create a classical tree in width
 ******************************************************************************/
template <class T, class Function>
void add_to_tree_in_width(Node<T> &node, int depth, int width,
                          Function const &function) {
  if (depth <= 0) {
    return;
  }

  int i = width;
  while (i--) {
    node.children.emplace_back(function());
  }

  for (auto &c : node.children) {
    add_to_tree_in_width<T>(c, depth - 1, width, function);
  }
}

template <class T, class Function>
Tree<T> create_tree_in_width(int depth, int width, Function const &function) {
  if (depth <= 0 || width <= 0) {
    return Tree<T>();
  }

  Tree<T> tree(function());
  add_to_tree_in_width<T>(tree.root(), --depth, width, function);
  return tree;
}

/*
 * Create a contiguous tree in width
 ******************************************************************************/
template <class T, class Function>
void add_to_contiguous_tree_in_width(
    typename contiguous::Tree<T>::Node_ptr node, int depth, int width,
    Function const &function) {
  if (depth <= 0) {
    return;
  }

  int i = width;
  while (i--) {
    node.add_child(function());
  }

  for (auto c = node.children_begin(); !!c; c = c.next_child()) {
    add_to_contiguous_tree_in_width<T>(c, depth - 1, width, function);
  }
}

template <class T, class Function>
contiguous::Tree<T> create_contiguous_tree_in_width(int depth, int width,
                                                    Function const &function) {
  if (depth <= 0 || width <= 0) {
    return contiguous::Tree<T>();
  }

  contiguous::Tree<T> tree(function());
  add_to_contiguous_tree_in_width<T>(tree.root(), --depth, width, function);
  return tree;
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void iterate_in_depth(Node<T> const &node, Function const &function) {
  function(node.data);

  for (auto &c : node.children) {
    iterate_in_depth<T>(c, function);
  }
}

template <class T, class Function>
void iterate_in_depth(Tree<T> const &tree, Function const &function) {
  if (tree.empty()) {
    return;
  }
  iterate_in_depth<T>(tree.root(), function);
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void iterate_in_depth(typename contiguous::Tree<T>::Node_cptr node,
                      Function const &function) {
  if (!node) {
    return;
  }

  function(node->data());

  for (auto c = node.children_begin(); !!c; c = c.next_child()) {
    iterate_in_depth<T>(c, function);
  }
}

template <class T, class Function>
void iterate_in_depth(contiguous::Tree<T> const &tree,
                      Function const &function) {
  iterate_in_depth<T>(tree.root(), function);
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void iterate_in_width(Node<T> const &node, Function const &function) {
  for (auto &c : node.children) {
    function(c.data);
  }

  for (auto &c : node.children) {
    iterate_in_width<T>(c, function);
  }
}

template <class T, class Function>
void iterate_in_width(Tree<T> const &tree, Function const &function) {
  if (tree.empty()) {
    return;
  }

  function(tree.root().data);
  iterate_in_width<T>(tree.root(), function);
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void iterate_in_width(typename contiguous::Tree<T>::Node_cptr node,
                      Function const &function) {
  for (auto c = node.children_begin(); !!c; c = c.next_child()) {
    function(c->data());
  }

  for (auto c = node.children_begin(); !!c; c = c.next_child()) {
    iterate_in_width<T>(c, function);
  }
}

template <class T, class Function>
void iterate_in_width(contiguous::Tree<T> const &tree,
                      Function const &function) {
  if (auto root = tree.root()) {
    function(root->data());
    iterate_in_width<T>(root, function);
  }
}