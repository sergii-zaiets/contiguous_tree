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
    Ptr(Ptr const &) = default;
    Ptr(Ptr &&) = default;
    Ptr &operator=(Ptr const &) = default;
    Ptr &operator=(Ptr &&) = default;

    operator bool() const { return !!nodes_; }

    Ptr &operator++() {
      Ptr n{nodes_->at(index_).next_sibling_,
            nodes_->at(index_).next_sibling_ ? nodes_ : nullptr};
      index_ = n.index_;
      nodes_ = n.nodes_;
      return *this;
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

    auto &operator*() { return nodes_->at(index_); }
    auto &operator*() const { return nodes_->at(index_); }
  };

  using Node_ptr = Ptr<Node>;
  using Node_cptr = Ptr<Node const>;

  Tree() = default;
  Tree(size_t reserve) { nodes_.reserve(reserve); }

  bool empty() const { return nodes_.empty(); }

  auto size() const { return nodes_.size(); }

  Node_ptr create_top(T &&data) {
    // ASSERT_RUNTIME(nodes_.empty());
    nodes_.emplace_back(std::forward<T>(data));
    return Node_ptr(nodes_.size() - 1, &nodes_);
  }

  Node_ptr top() {
    ASSERT_RUNTIME(!nodes_.empty());
    return Node_ptr(0, &nodes_);
  }

  Node_cptr top() const {
    ASSERT_RUNTIME(!nodes_.empty());
    return Node_cptr(0, &nodes_);
  }

  // void add_tree_as_child(Node_ptr nptr, Tree const &tree) {
  //   // TODO: check if tree is empty
  //   auto offset = nodes_.size();

  //   if (!nptr->children_begin_) {
  //     nptr->children_begin_ = offset;
  //   } else {
  //     nptr = {nptr->children_begin_, &nodes_};
  //     while (nptr->next_sibling_) {
  //       nptr = {nptr->next_sibling_, &nodes_};
  //     }
  //     nptr->next_sibling_ = offset;
  //   }

  //   auto start = nodes_.insert(std::end(nodes_), std::begin(tree.nodes_),
  //                              std::end(tree.nodes_));
  //   while (start != nodes_.end()) {
  //     if (start->children_begin_)
  //       start->children_begin_ += offset;
  //     if (start->next_sibling_)
  //       start->next_sibling_ += offset;
  //     start++;
  //   }
  // }

  Node_ptr children_begin(Node_ptr nptr) {
    return {nptr->children_begin_, nptr->children_begin_ ? &nodes_ : nullptr};
  }

  Node_cptr children_begin(Node_cptr nptr) const {
    return {nptr->children_begin_, nptr->children_begin_ ? &nodes_ : nullptr};
  }

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