#include <vector>

template <class T>
class Tree
{
public:
  class Node
  {
  public:
    T value_;
    std::vector<Node> nodes_;
    Node(T value) : value_(value) {}
  };

  Tree(T value) : root_(value) {}

private:
  Node root_;
};