#include <iostream>
#include <vector>

template <class T>
class Contiguous_node
{
  T data_;
  size_t children_begin_;
  size_t children_end_;
  std::vector<Contiguous_node> *nodes_;
  bool owns_; // TODO: can be removed

  Contiguous_node(size_t children_begin,
                  size_t children_end,
                  std::vector<T> *nodes_,
                  bool owns)
  {
    // on init children_begin = children_begin = index
  }

public:
  ~Contiguous_node()
  {
    if (owns_)
    {
      delete nodes_;
    }
  }

  Contiguous_node(T data)
  {
    nodes_ = new std::vector<T>();
    nodes_->push_back(data);
    owns_ = true;
    children_begin = children_begin = 0;
  }

  T &data() { return data_; }

  Contiguous_node add_child(T data) { children_.push_back(T); }

  template std::vector<T>::const_iterator children_begin() const;
  template std::vector<T>::const_iterator children_end() const;
};