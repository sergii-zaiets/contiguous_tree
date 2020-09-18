#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>

namespace contiguous {

/*
 * Contiguous tree implentation: very simple and naive
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
    size_t children_begin_{}; // default 0 - no children
    size_t next_sibling_{};   // default 0 - no siblings
  };

  template <class N> class Ptr;

  using Node_ptr = Ptr<Node>;
  using Node_cptr = Ptr<Node const>;

  template <class N> class Ptr {
    friend class Tree;
    using vector_type =
        std::conditional_t<std::is_const<N>::value, std::vector<Node> const,
                           std::vector<Node>>;
    size_t index_;
    vector_type *nodes_;
    Ptr(size_t index, vector_type *nodes) : index_(index), nodes_(nodes) {}

  public:
    Ptr(Ptr const &) = default;
    Ptr(Ptr &&) = default;
    Ptr &operator=(Ptr const &) = default;
    Ptr &operator=(Ptr &&) = default;

    template <class U>
    Ptr(Ptr<U> rhs) : index_(rhs.index_), nodes_(rhs.nodes_) {}

    operator bool() const { return !!nodes_; }

    Ptr next_child() const {
      return {nodes_->at(index_).next_sibling_,
              nodes_->at(index_).next_sibling_ ? nodes_ : nullptr};
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

  Tree() = default;
  Tree(T &&data) { nodes_.emplace_back(std::forward<T>(data)); }

  bool empty() const { return nodes_.empty(); }
  auto size() const { return nodes_.size(); }
  void reserve(size_t reserve) { nodes_.reserve(reserve); }

  Node_ptr root() { return Node_ptr(0, nodes_.empty() ? nullptr : &nodes_); }
  Node_cptr root() const {
    return Node_cptr(0, nodes_.empty() ? nullptr : &nodes_);
  }

  template <class Function> void for_each(Function f) const {
    std::for_each(nodes_.begin(), nodes_.end(),
                  [&](Node const &n) { f(n.data()); });
  }

private:
  std::vector<Node> nodes_;
};

} // namespace contiguous