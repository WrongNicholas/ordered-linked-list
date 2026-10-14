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
  ordered_linked_list();
  ~ordered_linked_list() = default;
  
  void add_item(T* ptr);

  T* front();
  T* back();

  // Iterators
  class iterator {
  private:
    list_node<T>* current;
  public:
    T* operator*() { return current->ptr; }
    list_node<T>* get_node() { return current; }
    iterator& operator++() { current = current->next; return *this; }
    bool operator==(const iterator& other) const { return current == other.current; }
    bool operator!=(const iterator& other) const { return current != other.current; }
    iterator(list_node<T>* node) : current(node) { }
  };

  iterator begin() { return iterator(m_head); }
  iterator end() { return iterator(nullptr); }

private:
  list_node<T>* m_head;
  list_node<T>* m_tail;
  std::size_t m_list_size;
};

template <typename T>
ordered_linked_list<T>::ordered_linked_list()
{
  m_head = nullptr;
  m_tail = nullptr;
  m_list_size = 0;
}

template <typename T>
void ordered_linked_list<T>::add_item(T* ptr)
{
  auto node = new list_node<T>(ptr);
  // list is empty
  if (m_list_size == 0)
  {
    m_list_size++;
    m_head = node;
    m_tail = node;
    return;
  }

  // test m_head
  if (*ptr < *m_head->ptr)
  {
    m_list_size++;
    node->next = m_head;
    m_head = node;
    return;
  }
  
  iterator it = begin();
  for (; it != end(); ++it)
  {
    // if it's next is null, break out of loop
    if (!it.get_node()->next)
    {
      // set m_tail because this will be last value
      m_tail = node;
      break;
    }

    if (*it.get_node()->next->ptr > *node->ptr)
    {
      node->next = it.get_node()->next;
      break;
    }
  }
  
  it.get_node()->next = node;

  m_list_size++;
}

template <typename T>
T* ordered_linked_list<T>::front()
{
  return m_head->ptr;
}

template <typename T>
T* ordered_linked_list<T>::back()
{
  return m_tail->ptr;
}

#endif
