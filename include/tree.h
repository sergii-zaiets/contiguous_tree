#include <memory>
#include <vector>

template <class T> struct Node {
  Node(T t) : data_(std::move(t)) {}
  Node(Node &&rhs)
      : data_(std::move(rhs.data_)), children_(std::move(rhs.children_)) {}
  Node(Node &rhs) = delete;

  T data_;
  std::vector<Node<T>> children_;
};

template <class T> struct Tree {
  Tree() {}
  Tree(T t) : root_(std::make_unique<Node<T>>(std::move(t))) {}

  bool empty() const { return !root_; }
  Node<T> const &root() const { return *root_; }
  Node<T> &root() { return *root_; }

private:
  std::unique_ptr<Node<T>> root_;
};