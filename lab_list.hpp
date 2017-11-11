#ifndef LAB_LIST_HPP_
#define LAB_LIST_HPP_
namespace Lab {
template<typename Type>
class list {
public:
  list();
  void push_back(const Type &elem);
  void push_front(const Type &elem);

  class iterator {
  public:
    Type &operator*();
    // assume zht asking for prefix increment
    // make him unhappy
    iterator &operator++();
    iterator &operator--();
    bool operator==(const iterator &another) const;
    bool operator!=(const iterator &another) const;
  private:
    // add your data and function here
  };

  iterator begin();
  iterator end();
  int size() const;
  void pop_front();
  void pop_back();
  void erase(iterator iter);
  void clear();
  ~list();

private:
  // add your data and function here
};
}

#endif
// (.*) \(\*(.*)\)\(.*?desc[,]?(.*)\)
// (.*)\(\*(.*)\)\(.*?iter[,]?(.*)\)