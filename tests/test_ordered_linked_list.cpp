#include <gtest/gtest.h>
#include <include/ordered_linked_list.hpp>

struct ExampleComparableType
{
  int value;
  bool operator<(const ExampleComparableType& other) const
  {
    return value < other.value;
  }

  bool operator>(const ExampleComparableType& other) const
  {
    return value > other.value;
  }

  bool operator==(const ExampleComparableType& other) const 
  {
    return value == other.value;
  }

  ExampleComparableType(int value) : value(value) { }
};

TEST(OrderedLinkedListTest, ExampleTest)
{
  ordered_linked_list<ExampleComparableType> l;

  auto* var1 = new ExampleComparableType(1);
  l.add_item(var1);

  ASSERT_EQ(*l.front(), *l.back());
}

TEST(OrderedLinkedListTest, AddItemInsertsItemsInCorrectLocation)
{
  ordered_linked_list<ExampleComparableType> l;

  auto* var1 = new ExampleComparableType(1);
  auto* var2 = new ExampleComparableType(0);
  auto* var3 = new ExampleComparableType(2);

  l.add_item(var1);
  l.add_item(var2);
  l.add_item(var3);

  auto it = l.begin();
  ASSERT_EQ(*(*it), 0);
  ++it;
  ASSERT_EQ(*(*it), 1);
  ++it;
  ASSERT_EQ(*(*it), 2);
}
