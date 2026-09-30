// ordered_linked_list.hpp
#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H

#include <cstddef>

template <typename T>
struct list_node {

  T* ptr;
  list_node* next;

  list_node(T* ptr) : ptr(ptr), next(nullptr) {}
};

template <typename T>
class ordered_linked_list {
public:

  // TODO: see if these need to be adjusted
  ordered_linked_list() = default;
  ~ordered_linked_list() = default;
  
  void add_item(T* ptr);

  // Utility
  void print();

  // Iterators
  class iterator {
  private:
    list_node<T>* current;
  public:
    T* operator*() { return current->ptr; }
    list_node<T>* get_node() { return current; }
    iterator& operator++() { current = current->next; return *this; }
    bool operator==(const iterator& other) const { return current->ptr == other.current->ptr; }
  };

private:
  list_node<T>* head = nullptr;
  std::size_t list_size = 0;
};

template <typename T>
void ordered_linked_list<T>::add_item(T* ptr)
{

}

#endif
