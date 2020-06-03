#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
class Contiguous_node
{
  T data_;
  size_t index_;
  size_t children_begin_;
  size_t children_end_;
  std::vector<Contiguous_node> *nodes_;

  Contiguous_node(T data, std::vector<T> *nodes);

public:
  using const_iterator = typename std::vector<T>::const_iterator;

  Contiguous_node(T data);
  ~Contiguous_node();

  Contiguous_node(Contiguous_node &) = delete;
  Contiguous_node(Contiguous_node &&) = delete;
  Contiguous_node &operator==(Contiguous_node const &rhs) const = delete;

  T &data();
  T const &data() const;

  Contiguous_node& add_child(T data);

  const_iterator children_begin() const;
  const_iterator children_end() const;
};

template <class T>
Contiguous_node<T>::Contiguous_node(T data, std::vector<T> *nodes)
    : data_(std::move(data)), nodes_(nodes) {}

template <class T>
Contiguous_node<T>::Contiguous_node(T data) : data_(std::move(data))
{
  nodes_ = new std::vector<T>();
  children_begin_ = children_end_ = index_ = 0;
}

template <class T>
Contiguous_node<T>::~Contiguous_node()
{
  if (index_)
  {
    delete nodes_;
  }
}

template <class T>
T &Contiguous_node<T>::data() { return data_; }

template <class T>
T const &Contiguous_node<T>::data() const { return data_; }

template <class T>
Contiguous_node<T>& Contiguous_node<T>::add_child(T data)
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
                [ce = children_end_](Contiguous_node const &n) {
                  n.index += 1 * (n.index >= ce);
                  n.children_begin_ += 1 * (n.children_begin_ >= ce);
                  n.children_end_ += 1 * (n.children_end_ >= ce);
                });

  auto it = nodes_->emplace(std::begin(*nodes_, children_end_),
                            std::move(data), nodes_);

  nodes_->back().index_ = children_end_;
  nodes_->back().children_begin_ = children_end_;
  nodes_->back().children_end_ = children_end_;

  return *it;
}

template <class T>
typename Contiguous_node<T>::const_iterator Contiguous_node<T>::children_begin() const
{
  return std::begin(*nodes_, children_begin_);
}

template <class T>
typename Contiguous_node<T>::const_iterator Contiguous_node<T>::children_end() const
{
  return std::begin(*nodes_, children_end_);
}
