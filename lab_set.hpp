#ifndef LAB_SET_HPP_
#define LAB_SET_HPP_

#include "labafx.hpp"

// DO NOT MODIFY BELOW

namespace Lab {
template <typename T> class set {
public:
  set();
  int size() const;
  void insert(const T &item);
  class iterator {
  public:
    const T &operator*();
    iterator operator++(int); // for iter++
    iterator operator--(int);
    iterator& operator++();
    bool operator==(const iterator &another) const;
    bool operator!=(const iterator &another) const;
  private:
    // add your data and function here
  };
  iterator find(const T &item);
  void erase(iterator it);
  iterator begin();
  iterator end();
  void clear();
  ~set();

private:
  // add your data and function here
};
}
#endif