#pragma once

#include <algorithm>
#include <vector>
#include <type_traits>

namespace contiguous {

/*
 *
 */
template <class T>
class Tree {
  struct private_ctor_t {};

 public:
  class Node {
    friend class Tree;

   public:
    Node(private_ctor_t, T data, size_t children_begin, size_t next_sibling)
        : data_(std::move(data)),
          children_begin_(children_begin),
          next_sibling_(next_sibling) {}

    T& data() { return data_; }
    T const& data() const { return data_; }

   private:
#ifdef ENABLE_UNIT_TEST_CTORS
   public:
#endif
    T data_;
    size_t children_begin_;
    size_t next_sibling_;
  };

  template <class N>
  class Ptr {
    friend class Tree;
    using vector_type =
        std::conditional_t<std::is_const<N>::value, const std::vector<Node>,
                           std::vector<Node>>;
    size_t index_;
    vector_type* nodes_;
    Ptr(size_t index, vector_type* nodes) : index_(index), nodes_(nodes) {}

   public:
    Ptr(Ptr const&) = default;
    Ptr(Ptr&&) = default;
    Ptr& operator=(Ptr const&) = default;
    Ptr& operator=(Ptr&&) = default;

    operator bool() const { return !!nodes_; }

    Ptr& operator++() {
      Ptr n{nodes_->at(index_).next_sibling_,
            nodes_->at(index_).next_sibling_ ? nodes_ : nullptr};
      index_ = n.index_;
      nodes_ = n.nodes_;
      return *this;
    }

    auto operator->() const { return &nodes_->at(index_); }
    auto& operator*() const { return nodes_->at(index_); }
  };

  using Node_ptr = Ptr<Node>;
  using Node_cptr = Ptr<Node const>;

  Tree() = default;
  Tree(size_t reserve) { nodes_.reserve(reserve); }

  bool empty() const { return nodes_.empty(); }

  auto size() const { return nodes_.size(); }

  Node_ptr create_top(T data) {
    ASSERT_RUNTIME(nodes_.empty());
    nodes_.emplace_back(private_ctor_t{}, std::move(data), 0, 0);
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

  Node_ptr add_child(Node_ptr nptr, T data) {
    if (!nptr->children_begin_) {
      nodes_.emplace_back(private_ctor_t{}, std::move(data), 0, 0);
      nptr->children_begin_ = nodes_.size() - 1;
    } else {
      nptr = {nptr->children_begin_, &nodes_};
      while (nptr->next_sibling_) {
        nptr = {nptr->next_sibling_, &nodes_};
      }
      nodes_.emplace_back(private_ctor_t{}, std::move(data), 0, 0);
      nptr->next_sibling_ = nodes_.size() - 1;
    }
    return {nodes_.size() - 1, &nodes_};
  }

  void add_tree_as_child(Node_ptr nptr, Tree const& tree) {
    // TODO: check if tree is empty
    auto offset = nodes_.size();

    if (!nptr->children_begin_) {
      nptr->children_begin_ = offset;
    } else {
      nptr = {nptr->children_begin_, &nodes_};
      while (nptr->next_sibling_) {
        nptr = {nptr->next_sibling_, &nodes_};
      }
      nptr->next_sibling_ = offset;
    }

    auto start = nodes_.insert(std::end(nodes_), std::begin(tree.nodes_),
                               std::end(tree.nodes_));
    while (start != nodes_.end()) {
      if (start->children_begin_) start->children_begin_ += offset;
      if (start->next_sibling_) start->next_sibling_ += offset;
      start++;
    }
  }

  Node_ptr children_begin(Node_ptr nptr) {
    return {nptr->children_begin_, nptr->children_begin_ ? &nodes_ : nullptr};
  }

  Node_cptr children_begin(Node_cptr nptr) const {
    return {nptr->children_begin_, nptr->children_begin_ ? &nodes_ : nullptr};
  }

  template <class Function>
  void for_each(Function f) const {
    if (nodes_.empty()) return;
    std::for_each(nodes_.begin(), nodes_.end(),
                  [&](Node const& n) { f(n.data()); });
  }

 private:
#ifdef ENABLE_UNIT_TEST_CTORS
 public:
#endif
  std::vector<Node> nodes_;
};

}  // namespace contiguous