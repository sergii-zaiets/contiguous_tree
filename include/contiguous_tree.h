#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>

namespace contiguous {

/*
 *
 */
template <class T> class Tree {
public:
  class Node {
    friend class Tree;

  public:
    Node(T &&data) : data_(std::forward<T>(data)) {}

    T &data() { return data_; }
    T const &data() const { return data_; }

  private:
    T data_;
    size_t children_begin_{};
    size_t next_sibling_{};
  };

  template <class N> class Ptr {
    friend class Tree;
    using vector_type =
        std::conditional_t<std::is_const<N>::value, const std::vector<Node>,
                           std::vector<Node>>;
    size_t index_;
    vector_type *nodes_;
    Ptr(size_t index, vector_type *nodes) : index_(index), nodes_(nodes) {}

  public:
    operator bool() const { return !!nodes_; }

    Ptr &operator++() {
      Ptr n{nodes_->at(index_).next_sibling_,
            nodes_->at(index_).next_sibling_ ? nodes_ : nullptr};
      index_ = n.index_;
      nodes_ = n.nodes_;
      return *this;
    }

    Ptr children_begin() const {
      auto cb = nodes_->at(index_).children_begin_;
      return {cb, cb ? nodes_ : nullptr};
    }

    Ptr add_child(T &&data) {
      auto *ptr = &nodes_->at(index_).children_begin_;
      while (*ptr) {
        ptr = &nodes_->at(*ptr).next_sibling_;
      }
      *ptr = nodes_->size();
      nodes_->emplace_back(std::forward<T>(data));
      return {nodes_->size() - 1, nodes_};
    }

    auto operator->() { return &nodes_->at(index_); }
    auto operator->() const { return &nodes_->at(index_); }
  };

  using Node_ptr = Ptr<Node>;
  using Node_cptr = Ptr<Node const>;

  Tree() = default;
  Tree(T &&data) { nodes_.emplace_back(std::forward<T>(data)); }

  bool empty() const { return nodes_.empty(); }
  auto size() const { return nodes_.size(); }
  void reserve(size_t reserve) { nodes_.reserve(reserve); }

  Node_ptr root() { return Node_ptr(0, nodes_.empty() ? nullptr : &nodes_); }

  template <class Function> void for_each(Function f) const {
    if (nodes_.empty())
      return;
    std::for_each(nodes_.begin(), nodes_.end(),
                  [&](Node const &n) { f(n.data()); });
  }

private:
  std::vector<Node> nodes_;
};

} // namespace contiguous