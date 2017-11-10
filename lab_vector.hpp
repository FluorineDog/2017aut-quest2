#ifndef LAB_VECTOR_HPP_
#define LAB_VECTOR_HPP_

#include "labafx.hpp"
namespace Lab {
template <typename T> class vector {
public:
  vector();
  class iterator {
  public:
    T &operator*();
    iterator operator+(int n);
    // zht does not require the followings, make him happy.
    // NOOOOOOOOOOOOO!
    iterator& operator++();
    bool operator==(const iterator &another) const;
    bool operator!=(const iterator &another) const;
    // iterator operator++(int);
  private:
    // add your data and function here
  };
  iterator begin();
  iterator end();
  size_t size() const;
  void push_back(const T &item);
  void pop_back();
  void erase(iterator iter);
  void clear();
  size_t capacity();
  void shrink_to_fit();
  void reserve(size_t resv_size);
  ~vector();

private:
  // add your data and function here
};
}

#endif