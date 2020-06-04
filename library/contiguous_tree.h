#pragma once

#include <algorithm>
#include <vector>

namespace contiguous_tree
{

  /*
 *
 */
  template <class T>
  class Node
  {
    T data_;
    size_t index_;
    size_t children_begin_;
    size_t children_end_;
    std::vector<Node> *nodes_;

    Node(T data, std::vector<T> *nodes);

  public:
    using const_iterator = typename std::vector<T>::const_iterator;

    Node(T data);
    ~Node();

    Node(Node &) = delete;
    Node(Node &&) = delete;
    Node &operator==(Node const &rhs) const = delete;

    T &data();
    T const &data() const;

    Node &add_child(T data);

    const_iterator children_begin() const;
    const_iterator children_end() const;
  };

  //
  // definitions
  //______________________________________________________________________________
  template <class T>
  Node<T>::Node(T data, std::vector<T> *nodes)
      : data_(std::move(data)), nodes_(nodes) {}

  template <class T>
  Node<T>::Node(T data) : data_(std::move(data))
  {
    nodes_ = new std::vector<T>();
    children_begin_ = children_end_ = index_ = 0;
  }

  template <class T>
  Node<T>::~Node()
  {
    if (index_)
    {
      delete nodes_;
    }
  }

  template <class T>
  T &Node<T>::data()
  {
    return data_;
  }

  template <class T>
  T const &Node<T>::data() const
  {
    return data_;
  }

  template <class T>
  Node<T> &Node<T>::add_child(T data)
  {
    if (index_ == children_begin_)
    { // if no children - add one
      nodes_->emplace_back(std::move(data), nodes_);

      nodes_->back().index_ = nodes_->size() - 1;
      nodes_->back().children_begin_ = nodes_->size() - 1;
      nodes_->back().children_end_ = nodes_->size() - 1;

      children_begin_ = nodes_->back().children_begin_ = nodes_->size() - 1;
      children_end_ = nodes_->back().children_end_ = nodes_->size();

      return nodes_->back();
    }

    std::for_each(std::begin(*nodes_), std::end(*nodes_),
                  [ce = children_end_](Node const &n) {
                    n.index += 1 * (n.index >= ce);
                    n.children_begin_ += 1 * (n.children_begin_ >= ce);
                    n.children_end_ += 1 * (n.children_end_ >= ce);
                  });

    auto it = nodes_->emplace(std::begin(*nodes_, children_end_), std::move(data),
                              nodes_);

    nodes_->back().index_ = children_end_;
    nodes_->back().children_begin_ = children_end_;
    nodes_->back().children_end_ = children_end_;

    return *it;
  }

  template <class T>
  typename Node<T>::const_iterator Node<T>::children_begin() const
  {
    return std::begin(*nodes_, children_begin_);
  }

  template <class T>
  typename Node<T>::const_iterator Node<T>::children_end() const
  {
    return std::begin(*nodes_, children_end_);
  }

} // namespace contiguous_tree