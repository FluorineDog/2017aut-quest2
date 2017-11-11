#ifndef LAB_PRIORITY_QUEUE
#define LAB_PRIORITY_QUEUE

#include "labafx.hpp"

namespace Lab {

template <typename value_t, typename Comp = Lab::less<value_t>> 
class priority_queue {
public:
  priority_queue();
  int size() const;
  void push(const value_t &);
  const value_t &top() const;
  void pop();
  ~priority_queue();
private:
  // add your data and function here
};
}

#endif