#include "../include/ordered_linked_list.hpp"
#include <iostream>

struct MyType
{
  int value;
  bool operator<(const MyType& other)
  {
    return value < other.value;
  }

  bool operator>(const MyType& other)
  {
    return value > other.value;
  }

  bool operator==(const MyType& other)
  {
    return value == other.value;
  }

  MyType(int value) : value(value) { }
};

int main()
{
  ordered_linked_list<MyType> l;

  auto* var1 = new MyType(1);
  auto* var2 = new MyType(2);
  auto* var3 = new MyType(0);
  auto* var4 = new MyType(4);
  auto* var5 = new MyType(-10);
  auto* var6 = new MyType(4);
  auto* var7 = new MyType(0);

  l.add_item(var1);
  l.add_item(var2);
  l.add_item(var3);
  l.add_item(var4);
  l.add_item(var5);
  l.add_item(var6);
  l.add_item(var7);

  for (ordered_linked_list<MyType>::iterator it = l.begin(); it != l.end(); ++it)
  {
    std::cout << (*(*it)).value << std::endl;
  }

  return 0;
}
