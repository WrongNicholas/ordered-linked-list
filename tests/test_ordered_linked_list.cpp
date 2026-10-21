#include <chrono>
#include <gtest/gtest.h>
#include <include/ordered_linked_list.hpp>
#include <include/student.hpp>

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

TEST(OrderedLinkedListTest, AddItem_CorrectOrder)
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

TEST(OrderedLinkedList, TestReverseIterators)
{
  ordered_linked_list<ExampleComparableType> l;

  auto* var1 = new ExampleComparableType(1);
  auto* var2 = new ExampleComparableType(0);
  auto* var3 = new ExampleComparableType(2);

  l.add_item(var1);
  l.add_item(var2);
  l.add_item(var3);

  auto it = l.rbegin();
  ASSERT_EQ(*(*it), 2);
  --it;
  ASSERT_EQ(*(*it), 1);
  --it;
  ASSERT_EQ(*(*it), 0);
  --it;
}

TEST(OrderedLinkedList, TestGetItem_HasItem_RemovesSuccessfully)
{
  ordered_linked_list<ExampleComparableType> l;

  auto* var1 = new ExampleComparableType(1);
  auto* var2 = new ExampleComparableType(0);
  auto* var3 = new ExampleComparableType(2);
  auto* var4 = new ExampleComparableType(3);
  auto* var5 = new ExampleComparableType(4);

  l.add_item(var1);
  l.add_item(var2);
  l.add_item(var3);
  l.add_item(var4);
  l.add_item(var5);

  auto* got_item = l.get_item(var3);
  ASSERT_EQ(*got_item, *var3);

  auto it = l.begin();
  ASSERT_EQ(*(*it), 0);
  ++it;
  ASSERT_EQ(*(*it), 1);
  ++it;
  ASSERT_EQ(*(*it), 3);
  ++it;
  ASSERT_EQ(*(*it), 4);

  got_item = l.get_item(var2);
  ASSERT_EQ(*got_item, *var2);

  it = l.begin();
  ASSERT_EQ(*(*it), 1);
  ++it;
  ASSERT_EQ(*(*it), 3);
  ++it;
  ASSERT_EQ(*(*it), 4);

  got_item = l.get_item(var5);
  ASSERT_EQ(*got_item, *var5);

  it = l.begin();
  ASSERT_EQ(*(*it), 1);
  ++it;
  ASSERT_EQ(*(*it), 3);
}

TEST(OrderedLinkedListTestWithStudent, AddItem_CorrectOrder)
{
  ordered_linked_list<student> l;

  auto* student1 = new student("Michael", "Wojnar", "M00000002", std::chrono::year_month_day(std::chrono::year(2004), std::chrono::month(5), std::chrono::day(5)));
  auto* student2 = new student("Ben", "Lastname", "M00000004", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student3 = new student("Connor", "LastName", "M00000001", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student4 = new student("Another", "Person", "M00000003", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));

  l.add_item(student1);
  l.add_item(student2);
  l.add_item(student3);
  l.add_item(student4);
  
  auto it = l.begin();
  ASSERT_EQ((*it)->get_name(), "Connor LastName");
  ++it;
  ASSERT_EQ((*it)->get_name(), "Michael Wojnar");
  ++it;
  ASSERT_EQ((*it)->get_name(), "Another Person");
  ++it;
  ASSERT_EQ((*it)->get_name(), "Ben Lastname");
}

TEST(OrderedLinkedListTest, IsInList_AndIsInList)
{
  ordered_linked_list<student> l;

  auto* student1 = new student("Michael", "Wojnar", "M00000002", std::chrono::year_month_day(std::chrono::year(2004), std::chrono::month(5), std::chrono::day(5)));
  auto* student2 = new student("Ben", "Lastname", "M00000004", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student3 = new student("Connor", "LastName", "M00000001", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student4 = new student("Another", "Person", "M00000003", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));

  l.add_item(student1);
  l.add_item(student2);
  l.add_item(student3);
  l.add_item(student4);
  
  ASSERT_TRUE(l.is_in_list(student1));
  ASSERT_TRUE(l.is_in_list(student2));
  ASSERT_TRUE(l.is_in_list(student3));
  ASSERT_TRUE(l.is_in_list(student4));
}

TEST(OrderedLinkedListTest, IsInList_AndIsNOTInList)
{
  ordered_linked_list<student> l;

  auto* student1 = new student("Michael", "Wojnar", "M00000002", std::chrono::year_month_day(std::chrono::year(2004), std::chrono::month(5), std::chrono::day(5)));
  auto* student2 = new student("Ben", "Lastname", "M00000004", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student3 = new student("Connor", "LastName", "M00000001", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student4 = new student("Another", "Person", "M00000003", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));

  auto* student5 = new student("NotA", "Student", "M1234567", std::chrono::year_month_day(std::chrono::year(1999), std::chrono::month(3), std::chrono::day(32)));

  l.add_item(student1);
  l.add_item(student2);
  l.add_item(student3);
  l.add_item(student4);
  
  ASSERT_FALSE(l.is_in_list(student5));
}

TEST(OrderedLinkedListTest, Empty_AndIsEmpty)
{
  ordered_linked_list<student> l;

  ASSERT_TRUE(l.is_empty());
}

TEST(OrderedLinkedListTest, Empty_AndIsNOTEmpty)
{
  ordered_linked_list<ExampleComparableType> l;

  l.add_item(new ExampleComparableType(3));

  ASSERT_FALSE(l.is_empty());
}


TEST(OrderedLinkedListTest, SizeReturnsCorrect)
{
  ordered_linked_list<student> l;

  auto* student1 = new student("Michael", "Wojnar", "M00000002", std::chrono::year_month_day(std::chrono::year(2004), std::chrono::month(5), std::chrono::day(5)));
  auto* student2 = new student("Ben", "Lastname", "M00000004", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student3 = new student("Connor", "LastName", "M00000001", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student4 = new student("Another", "Person", "M00000003", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));

  ASSERT_EQ(l.size(), 0);
  l.add_item(student1);
  ASSERT_EQ(l.size(), 1);
  l.add_item(student2);
  ASSERT_EQ(l.size(), 2);
  l.add_item(student3);
  ASSERT_EQ(l.size(), 3);
  l.add_item(student4);
  ASSERT_EQ(l.size(), 4);
}

TEST(OrderedLinkedListTest, SeeNext_AndSeeAt_ReturnsCorrectStuff_AndThenResetResetsProperly)
{
  ordered_linked_list<student> l;

  auto* student1 = new student("Michael", "Wojnar", "M00000002", std::chrono::year_month_day(std::chrono::year(2004), std::chrono::month(5), std::chrono::day(5)));
  auto* student2 = new student("Ben", "Lastname", "M00000004", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student3 = new student("Connor", "LastName", "M00000001", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));
  auto* student4 = new student("Another", "Person", "M00000003", std::chrono::year_month_day(std::chrono::year(1445), std::chrono::month(10), std::chrono::day(31)));

  l.add_item(student1); // m_iterator -> student1
  l.add_item(student2); 
  l.add_item(student3); // m_iterator still at student 1!!
  l.add_item(student4);

  ASSERT_EQ(l.see_next(), student1);
  ASSERT_EQ(l.see_next(), student4);
  ASSERT_EQ(l.see_next(), student2);
  ASSERT_EQ(l.see_next(), nullptr);
  ASSERT_EQ(l.see_next(), student3);

  // 0 : student3
  // 1 : student1
  // 2 : student4
  // 3 : student2

  ASSERT_EQ(l.see_at(2), student4);
  l.reset();
  ASSERT_EQ(l.see_next(), student3);
}
