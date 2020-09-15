#include <memory>
#include <vector>

template <class T> struct Node;

template <class T> struct Tree {
  Tree() {}
  Tree(T &&data) : root_(std::make_unique<Node<T>>(std::forward<T>(data))) {}

  bool empty() const { return !root_; }
  Node<T> const &root() const { return *root_; }
  Node<T> &root() { return *root_; }

private:
  std::unique_ptr<Node<T>> root_;
};

template <class T> struct Node {
  Node(T &&d) : data(std::forward<T>(d)) {}
  Node(Node &&rhs) = default;
  Node(Node &rhs) = delete;

  T data;
  std::vector<Node<T>> children;
};