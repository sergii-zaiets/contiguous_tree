#include <vector>

// template <class T>
// class Tree
// {
// public:
//   class Node
//   {
//   public:
//     T value_;
//     std::vector<Node> nodes_;
//     Node(T value) : value_(value) {}
//   };

//   Tree(T value) : root_(value) {}

// private:
//   Node root_;
// };

/*
 *
 */

template <class T>
class Node
{
  T data_;
  std::vector<T> children_;

public:
  Node(T data) : data_(std::move(data)) {}
  T &data() { return data_; }
  void add_child(T data) { children_.push_back(T); }
  std::vector<T> const &children() const { return children_; }
};