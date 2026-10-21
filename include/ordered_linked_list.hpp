// ordered_linked_list.hpp
#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H

#include <stdexcept>
#include <cstddef>
#include <iostream>

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

  ordered_linked_list();
  ordered_linked_list(const ordered_linked_list<T>& l);
  ~ordered_linked_list();

  ordered_linked_list& operator=(const ordered_linked_list& l);
  
  void add_item(T* ptr);
  T* get_item(T* ptr);
  bool is_in_list(T* ptr) const;
  bool is_empty() const;
  size_t size() const;

  T* see_next();
  T* see_at(int idx);
  void reset();

  void display_all() const;

  void remove_all();

  T* get_largest() const;
  T* get_smallest() const;

  void reverse();

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

  // is the list reversed?
  // yes, owen. i implemented it this way
  bool m_is_ascending = true;

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
ordered_linked_list<T>::ordered_linked_list(const ordered_linked_list<T>& l)
{
  m_head = nullptr;
  m_tail = nullptr;
  m_list_size = 0;

  for (auto it = l.begin(); it != l.end(); ++it)
  {
    
    add_item(*it);
  }
}

template <typename T>
ordered_linked_list<T>& ordered_linked_list<T>::operator=(const ordered_linked_list<T>& l)
{
  // test for self-assignment
  if (this == &l) return *this;

  remove_all();

  for (auto it = l.begin(); it != l.end(); ++it)
  {
    add_item(*it);
  }

  return *this;
}

template <typename T>
ordered_linked_list<T>::~ordered_linked_list<T>()
{
  remove_all();
}

template <typename T>
void ordered_linked_list<T>::remove_all()
{
  list_node<T>* current = m_head;

  while (current != nullptr)
  {
    list_node<T>* next = current->next;
    delete current;
    current = next;
  }

  m_head = nullptr;
  m_tail = nullptr;
  m_list_size = 0;
  m_iterator = begin();
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
  bool comparison = m_is_ascending ? *ptr < *m_head->ptr : *ptr > *m_head->ptr;
  if (comparison)
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

    bool comparison = m_is_ascending ? *it.get_node()->next->ptr > *node->ptr : *it.get_node()->next->ptr < *node->ptr;
    if (comparison)
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
    if (*ptr != **it)
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

    T* data = it.get_node()->ptr;
    delete it.get_node();
    
    // decrement m_list_size
    m_list_size--;

    // then return ptr
    return data;
    
  }

  return nullptr;
}

template <typename T>
bool ordered_linked_list<T>::is_in_list(T* ptr) const
{
  for (auto it = begin(); it != end(); ++it)
  {
    if (*ptr == **it)
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

  T* item_to_return = *it;
  m_iterator = it;
  ++m_iterator;
  return item_to_return;
}

template <typename T>
void ordered_linked_list<T>::reset()
{
  m_iterator = begin();
}

// forcing a use of .display() is ridiculous here.
// the point of a templated class is that it's supposed to be agnostic
// but, here we're forcing the templated class to have an odd non-standard display() method
template <typename T>
void ordered_linked_list<T>::display_all() const
{
  if (is_empty())
  {
    std::cout << " [HEAD] <--> [NULL]\n";
    return;
  }

  std::cout << "            [HEAD]\n";
  std::cout << "              |\n";
  std::cout << "              v\n";

  int index = 0;
  for (auto it = begin(); it != end(); ++it)
  {
    std::cout << " ===============================\n";
    std::cout << "        NODE [" << index << "]\n";
    std::cout << " -------------------------------\n";
    (*it)->display();

    std::cout << " ===============================\n";

    ++index;

    // checking to see if theres a next node
    auto next_it = it;
    ++next_it;
    if (next_it != end())
    {
      std::cout << "          ^   |\n";
      std::cout << "     prev |   | next\n";
      std::cout << "          |   v\n";
    }
  }

      std::cout << "              |\n";
      std::cout << "              v\n";
      std::cout << "            [NULL]\n";
}

template <typename T>
T* ordered_linked_list<T>::get_largest() const
{

  // list_node<T> current = m_head;
  // T* largest = m_head->ptr;
  // auto it = begin();
  // ++it;
  // for (; it != end(); ++it)
  // {
  //   if (*current.ptr > *largest)
  //   {
  //     largest = current.ptr;
  //   }
  // }
  //
  // return largest;
  //
  // NAH!
  // i did it cooler :
  
  if (is_empty()) return nullptr;
  return m_is_ascending ? m_tail->ptr : m_head->ptr;
}

template <typename T>
T* ordered_linked_list<T>::get_smallest() const
{
  // list_node<T> current = m_head;
  // T* smallest = m_head->ptr;
  // auto it = begin();
  // ++it;
  // for (; it != end(); ++it)
  // {
  //   if (*current.ptr < *smallest)
  //   {
  //     smallest = current.ptr;
  //   }
  // }
  //
  // return smallest;

  if (is_empty()) return nullptr;
  return m_is_ascending ? m_head->ptr : m_tail->ptr;
}

template <typename T>
void ordered_linked_list<T>::reverse()
{
  list_node<T>* current = m_head;
  list_node<T>* temp = nullptr;
  while (current != nullptr)
  {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    
    current = current->prev;
  }

  temp = m_head;
  m_head = m_tail;
  m_tail = temp;

  m_is_ascending = !m_is_ascending;

  reset();
}

#endif
