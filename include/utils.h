#pragma once

#include "contiguous_tree.h"
#include "tree.h"

/*
 * Create a classical tree in depth
 ******************************************************************************/
template <class T, class Function>
void add_to_tree_in_depth_impl(Node<T> &node, int depth, int width,
                               Function const &function) {
  if (depth <= 0) {
    return;
  }

  int i = width;
  while (i--) {
    node.children.emplace_back(function());
    add_to_tree_in_depth_impl(node.children.back(), depth - 1, width, function);
  }
}

template <class T, class Function>
Tree<T> create_tree_in_depth(int depth, int width, Function const &function) {
  if (depth <= 0 || width <= 0) {
    return Tree<T>();
  }

  Tree<T> tree(function());
  add_to_tree_in_depth_impl<T>(tree.root(), --depth, width, function);
  return tree;
}

/*
 * Create a contiguous tree in depth
 ******************************************************************************/
template <class T, class Function>
void add_to_contiguous_tree_in_depth_impl(
    typename contiguous::Tree<T>::Node_ptr node, int depth, int width,
    Function const &function) {
  if (depth <= 0) {
    return;
  }

  int i = width;
  while (i--) {
    auto child = node.add_child(function());
    add_to_contiguous_tree_in_depth_impl<T>(child, depth - 1, width, function);
  }
}

template <class T, class Function>
contiguous::Tree<T> create_contiguous_tree_in_depth(int depth, int width,
                                                    Function const &function) {
  if (depth <= 0 || width <= 0) {
    return contiguous::Tree<T>();
  }

  contiguous::Tree<T> tree(function());
  add_to_contiguous_tree_in_depth_impl<T>(tree.root(), --depth, width,
                                          function);
  return tree;
}

/*
 * Create a classical tree in width
 ******************************************************************************/
template <class T, class Function>
void add_to_tree_in_width_impl(std::vector<Node<T> *> const &nodes, int depth,
                               int width, Function const &function) {
  if (depth <= 0) {
    return;
  }

  std::vector<Node<T> *> children;

  for (auto n : nodes) {
    int i = width;
    while (i--) {
      n->children.emplace_back(function());
    }
  }

  for (auto n : nodes) {
    for (auto &c : n->children) {
      children.emplace_back(&c);
    }
  }

  add_to_tree_in_width_impl<T>(children, depth - 1, width, function);
}

template <class T, class Function>
Tree<T> create_tree_in_width(int depth, int width, Function const &function) {
  if (depth <= 0 || width <= 0) {
    return Tree<T>();
  }

  Tree<T> tree(function());
  add_to_tree_in_width_impl<T>({&tree.root()}, --depth, width, function);
  return tree;
}

/*
 * Create a contiguous tree in width
 ******************************************************************************/
template <class T, class Function>
void add_to_contiguous_tree_in_width_impl(
    std::vector<typename contiguous::Tree<T>::Node_ptr> const &nodes, int depth,
    int width, Function const &function) {
  if (depth <= 0) {
    return;
  }

  std::vector<typename contiguous::Tree<T>::Node_ptr> children;

  for (auto n : nodes) {
    int i = width;
    while (i--) {
      n.add_child(function());
    }
  }

  for (auto n : nodes) {
    for (auto c = n.children_begin(); !!c; c = c.next_child()) {
      children.emplace_back(c);
    }
  }

  add_to_contiguous_tree_in_width_impl<T>(children, depth - 1, width, function);
}

template <class T, class Function>
contiguous::Tree<T> create_contiguous_tree_in_width(int depth, int width,
                                                    Function const &function) {
  if (depth <= 0 || width <= 0) {
    return contiguous::Tree<T>();
  }

  contiguous::Tree<T> tree(function());
  add_to_contiguous_tree_in_width_impl<T>({tree.root()}, --depth, width,
                                          function);
  return tree;
}

/*
 * Iterate a classical tree in depth
 ******************************************************************************/
template <class T, class Function>
void iterate_in_depth_impl(Node<T> const &node, Function const &function) {
  function(node.data);

  for (auto &c : node.children) {
    iterate_in_depth_impl<T>(c, function);
  }
}

template <class T, class Function>
void iterate_in_depth(Tree<T> const &tree, Function const &function) {
  if (!tree.empty()) {
    iterate_in_depth_impl<T>(tree.root(), function);
  }
}

/*
 * Iterate a contiguous tree in depth
 ******************************************************************************/
template <class T, class Function>
void iterate_contiguous_in_depth_impl(
    typename contiguous::Tree<T>::Node_cptr node, Function const &function) {
  function(node->data());

  for (auto c = node.children_begin(); !!c; c = c.next_child()) {
    iterate_contiguous_in_depth_impl<T>(c, function);
  }
}

template <class T, class Function>
void iterate_contiguous_in_depth(contiguous::Tree<T> const &tree,
                                 Function const &function) {
  if (!tree.empty()) {
    iterate_contiguous_in_depth_impl<T>(tree.root(), function);
  }
}

/*
 * Iterate a classical tree in width
 ******************************************************************************/
template <class T, class Function>
void iterate_in_width_impl(std::vector<Node<T> const *> const &nodes,
                           Function const &function) {
  if (nodes.empty()) {
    return;
  }

  std::vector<Node<T> const *> children;

  for (auto n : nodes) {
    for (auto &c : n->children) {
      children.emplace_back(&c);
    }
  }

  for (auto np : children) {
    function(np->data);
  }

  iterate_in_width_impl<T>(children, function);
}

template <class T, class Function>
void iterate_in_width(Tree<T> const &tree, Function const &function) {
  if (!tree.empty()) {
    function(tree.root().data);
    iterate_in_width_impl<T>({&tree.root()}, function);
  }
}

/*
 * Iterate a contiguous tree in width
 ******************************************************************************/
template <class T, class Function>
void iterate_contiguous_in_width_impl(
    std::vector<typename contiguous::Tree<T>::Node_cptr> const &nodes,
    Function const &function) {
  if (nodes.empty()) {
    return;
  }

  std::vector<typename contiguous::Tree<T>::Node_cptr> children;

  for (auto n : nodes) {
    for (auto c = n.children_begin(); !!c; c = c.next_child()) {
      children.emplace_back(c);
    }
  }

  for (auto np : children) {
    function(np->data());
  }

  iterate_contiguous_in_width_impl<T>(children, function);
}

template <class T, class Function>
void iterate_contiguous_in_width(contiguous::Tree<T> const &tree,
                                 Function const &function) {
  if (auto root = tree.root()) {
    function(root->data());
    iterate_contiguous_in_width_impl<T>({root}, function);
  }
}