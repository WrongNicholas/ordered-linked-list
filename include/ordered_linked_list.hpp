// ordered_linked_list.hpp
#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H

#include <stdexcept>
#include <cstddef>

template <typename T>
struct list_node {

  T* ptr;
  list_node* next;
  list_node* prev;

  list_node(T* ptr) : ptr(ptr), next(nullptr), prev(nullptr) {}
};

template <typename T>
class ordered_linked_list {
public:

  // TODO: see if these need to be adjusted
  ordered_linked_list();
  ~ordered_linked_list();
  
  void add_item(T* ptr);
  T* get_item(T* ptr);
  bool is_in_list(T* ptr) const;
  bool is_empty() const;
  size_t size() const;

  T* see_next();
  T* see_at(int idx);
  void reset();

  T* front() const;
  T* back() const;

  // my beautiful iterators <3
  class iterator {
  private:
    list_node<T>* current;
  public:
    T* operator*() { return current->ptr; }
    list_node<T>* get_node() { return current; }
    iterator& operator++() { current = current->next; return *this; }
    iterator& operator--() { current = current->prev; return *this; }
    bool operator==(const iterator& other) const { return current == other.current; }
    bool operator!=(const iterator& other) const { return current != other.current; }
    iterator(list_node<T>* node) : current(node) { }
    iterator() : current(nullptr) {}
  };

  iterator begin() const { return iterator(m_head); }
  iterator end() const { return iterator(nullptr); }
  iterator rbegin() const { return iterator(m_tail); }
  iterator rend() const { return iterator(nullptr); }

private:
  list_node<T>* m_head;
  list_node<T>* m_tail;
  std::size_t m_list_size;

  // continuous iterator
  iterator m_iterator;
};

template <typename T>
ordered_linked_list<T>::ordered_linked_list()
{
  m_head = nullptr;
  m_tail = nullptr;
  m_list_size = 0;
}

template <typename T>
ordered_linked_list<T>::~ordered_linked_list<T>()
{
  list_node<T>* current = m_head;

  while (current != nullptr)
  {
    list_node<T>* next = current->next;
    delete current;
    current = next;
  }
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
    m_iterator = begin();
    return;
  }

  // test m_head
  if (*ptr < *m_head->ptr)
  {
    m_list_size++;
    node->next = m_head;
    m_head->prev = node;
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
      node->next->prev = node;
      break;
    }
  }
  
  it.get_node()->next = node;
  node->prev = it.get_node();

  m_list_size++;
}

template <typename T>
T* ordered_linked_list<T>::get_item(T* ptr)
{
  
  for (auto it = begin(); it != end(); ++it)
  {
    if (ptr != *it)
      continue;

    // remove from list
    if (it.get_node() == m_head)
    {
      m_head = it.get_node()->next;
    }
    else
    {
      it.get_node()->prev->next = it.get_node()->next;
    }

    if (it.get_node() == m_tail)
    {
      m_tail = it.get_node()->prev;
    }
    else
    {
      it.get_node()->next->prev = it.get_node()->prev;
    }

    if (m_iterator.get_node() == it.get_node())
    {
      ++m_iterator;
    }
    delete it.get_node();
    
    // decrement m_list_size
    m_list_size--;

    // then return ptr
    return ptr;
    
  }

  return nullptr;
}

template <typename T>
bool ordered_linked_list<T>::is_in_list(T* ptr) const
{
  for (auto it = begin(); it != end(); ++it)
  {
    if (ptr == *it)
      return true;
  }

  return false;
}

template <typename T>
bool ordered_linked_list<T>::is_empty() const
{
  return m_list_size == 0;
}

template <typename T>
size_t ordered_linked_list<T>::size() const
{
  return m_list_size;
}

template <typename T>
T* ordered_linked_list<T>::see_next()
{
  if (is_empty())
    throw std::runtime_error("List is empty!");

  if (m_iterator == end())
  {
    m_iterator = begin();
    return nullptr;
  }

  T* ptr = *m_iterator;
  ++m_iterator;
  return ptr;
}

template <typename T>
T* ordered_linked_list<T>::see_at(int idx)
{
  if (idx >= m_list_size || idx < 0)
    throw std::out_of_range("Index is out of range!");

  auto it = begin();
  int i = 0;
  for (; i < idx; ++i)
  {
    ++it;
  }

  m_iterator = it;
  return *m_iterator;
}

template <typename T>
void ordered_linked_list<T>::reset()
{
  m_iterator = begin();
}

template <typename T>
T* ordered_linked_list<T>::front() const
{
  return m_head->ptr;
}

template <typename T>
T* ordered_linked_list<T>::back() const
{
  return m_tail->ptr;
}

#endif
