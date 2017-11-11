#ifndef LAB_UNORDERED_MAP_HPP_
#define LAB_UNORDERED_MAP_HPP_

#include "labafx.hpp"
namespace Lab {
template <typename Key, typename Value, typename Hash = hash<Key>
          /*, typename KeyEqual=equal_to<Key> */>
// KeyEqual is not required by zht. Make him happy.
class unordered_map {
public:
  unordered_map();
  size_t size() const;
  void insert(::std::pair<Key, Value> kvpair);
  void clear();
  class iterator {
  public:
    // assume Key won't be modified
    // actually priviledge controling is hard
    // since zht doesn't require it. Make him happy
    ::std::pair<const Key, Value> &operator*();
    iterator operator++(int);
    iterator operator--(int);
    // prefix increment operator is not required by zht. Make him happy
    // NO.
    iterator &operator++();
    iterator &operator--();
    bool operator==(const iterator &another) const;
    bool operator!=(const iterator &another) const;
  private:
    // add your data and function here
  };
  iterator begin();
  iterator end();
  iterator find(const Key &item);
  void erase(iterator iter);
  ~unordered_map();

private:
  // add your data and function here
};
}
#endif