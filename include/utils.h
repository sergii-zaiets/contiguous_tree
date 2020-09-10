#include "contiguous_tree.h"
#include "tree.h"

/*
 *
 ******************************************************************************/
template <class T, class Function>
void add_to_tree(Node<T> &node, int depth, int width,
                 Function const &function) {
  if (depth <= 0)
    return;

  int i = width;
  while (i--) {
    node.children.emplace_back(function());
    add_to_tree(node.children.back(), depth - 1, width, function);
  }
}

template <class T, class Function>
Tree<T> create_tree(int depth, int width, Function const &function) {
  if (depth <= 0 || width <= 0)
    return Tree<T>();

  Tree<T> tree(function());
  add_to_tree(tree.root(), --depth, width, function);
  return tree;
}

/*
 *
 ******************************************************************************/
template <class T, class Function>
void add_to_contiguous_tree(typename contiguous::Tree<T>::Node_ptr node,
                            int depth, int width, Function const &function) {
  if (depth <= 0)
    return;

  int i = width;
  while (i--) {
    auto child = node.add_child(function());
    add_to_contiguous_tree<T>(child, depth - 1, width, function);
  }
}

template <class T, class Function>
contiguous::Tree<T> create_contiguous_tree(int depth, int width,
                                           Function const &function) {
  if (depth <= 0 || width <= 0)
    return contiguous::Tree<T>();

  contiguous::Tree<T> tree(function());
  add_to_contiguous_tree<T>(tree.root(), --depth, width, function);
  return tree;
}