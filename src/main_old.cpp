#include <include/ordered_linked_list.hpp>
#include <include/student.hpp>
#include <iostream>

student* create_student()
{
  std::cout << "Please enter the student's first name: ";
  std::string first_name;
  std::cin >> first_name;
  std::cout << "Please enter the student's last name: ";
  std::string last_name;
  std::cin >> last_name;
  std::cout << "Please enter the student's M Number (in format M12345678): ";
  std::string m_number;
  std::cin >> m_number;
  std::cout << "Please enter the student's birth year: ";
  int birth_year;
  std::cin >> birth_year;
  std::cout << "Please enter the student's birth month: ";
  int birth_month;
  std::cin >> birth_month;
  std::cout << "Please enter the student's birth day: ";
  int birth_day;
  std::cin >> birth_day;
  std::chrono::year_month_day date_of_birth = 
    std::chrono::year_month_day(
      std::chrono::year(birth_year),
      std::chrono::month(birth_month),
      std::chrono::day(birth_day)
  );
  std::cout << "Please enter a gpa (enter -1 if you don't care for one): ";
  float gpa;
  std::cin >> gpa;

  student* my_student = nullptr;
  if (gpa < 0)
    my_student = new student(first_name, last_name, m_number, date_of_birth);
  else
   my_student = new student(first_name, last_name, m_number, date_of_birth, gpa);
  
  return my_student;
}

int main()
{
  std::cout << "TASK 6!\n";


  // testing for task 5
  std::cout << "Task 5 Automated Tests...\n";
  ordered_linked_list<student> test_list1;
  student* test_student1 = new student("Michael", "Wojnar", "M00000001", std::chrono::year(2004) / std::chrono::month(5) / std::chrono::day(5), 3.8);
  student* test_student2 = new student("Owen", "Waller", "M00000002", std::chrono::year(1992) / std::chrono::month(9) / std::chrono::day(11), 0.6);
  test_list1.add_item(test_student1);
  test_list1.add_item(test_student2);

  ordered_linked_list<student> test_list2(test_list1);

  test_list1.remove_all();
  std::cout << "Test List 1:\n";
  test_list1.display_all();
  std::cout << "Test List 2:\n";
  test_list2.display_all();
  
  ordered_linked_list<student> test_list3;
  test_list3 = test_list1;
  std::cout << "Test List 3:\n";
  test_list3.display_all();
  std::cout << "End of Task 5 Automated Tests...\n";

  ordered_linked_list<student> l;

  while (true)
  {
    std::cout << "Welcome!\n";
    std::cout << "Select a method:\n [1] void add_item\n [2] T* get_item\n [3] bool is_in_list\n [4] size_t size() \n [5] T* see_next\n [6] T* see_at\n [7] void reset\n [8] display_all\n [9] remove_all\n [10] get_largest\n [11] get_smallest\n [12] reverse\n [13] is_empty\n [-1] Exit" << std::endl;
    int value;
    std::cin >> value;
    student* current_student = nullptr;
    
    switch (value)
    {
      case 1:
        current_student = create_student();
        l.add_item(current_student);
        std::cout << "Student added to list!\n";
        break;
      case 2:
        {
        std::cout << "Enter an MNumber to get and remove from the list: ";
        std::string m_number;
        std::cin >> m_number;
        
        student* dummy = new student("", "", m_number, std::chrono::year(2000) / std::chrono::month(1) / std::chrono::day(1));
        
        student* found_student = l.get_item(dummy);
        
        if (found_student) {
          std::cout << "Student " << found_student->get_name() << " was removed from the list!\n";
          delete found_student; 
        } else {
          std::cout << "Student was not found in the list!\n";
        }
        
        delete dummy; 
      }
      break;
      case 3:
        {
          std::cout << "Enter an MNumber to search for: ";
          std::string m_number;
          std::cin >> m_number;
          student* dummy = new student("", "", m_number, std::chrono::year(2000) / std::chrono::month(1) / std::chrono::day(1));

          if (l.is_in_list(dummy))
            std::cout << "Student is in list!\n";
          else
            std::cout << "Student was not in list!\n";

          delete dummy;
        }
        break;
      case 4:
        std::cout << "The list currently holds " << l.size() << " students!\n";
        break;
      case 5:
        current_student = l.see_next();
        if (current_student)
          std::cout << "Result of see_next was student of name " << current_student->get_name() << std::endl;
        else
         std::cout << "We have reached the end of the list! Try see_next() again to return to beginning of list!" << std::endl;
        break;
      case 6:
        std::cout << "See at which index? ";
        int index;
        std::cin >> index;
        try {

          current_student = l.see_at(index);
        }
        catch (std::out_of_range e)
        {
          std::cout << "An error was thrown: " << e.what() << std::endl;
        }
        if (current_student)
          std::cout << "Student at index " << index << " was studrnt of name " << current_student->get_name() << std::endl;
        break;
      case 7:
        l.reset();
        std::cout << "Internal iterator position has been reset to first element in list.\nTry see_next() to see!" << std::endl;
        break;
      case 8:
        l.display_all();
        break;
      case 9:
        l.remove_all();
        break;
      case 10:
        // get_largest
        {
          student* largest = l.get_largest();
          if (largest) {
              std::cout << "Largest value in linked list: \n";
              largest->display();
          } else {
              std::cout << "The list is empty!\n";
          }
        }
        break;
      case 11:
        // get_smallest
        {
          student* smallest = l.get_smallest();
          if (smallest) {
              std::cout << "Smallest value in linked list: \n";
              smallest->display();
          } else {
              std::cout << "The list is empty!\n";
          }
        }
        break;
      case 12:
        l.reverse();
        std::cout << "List has been reversed! Try display_all\n";
        break;
      case 13:
        if (l.is_empty())
          std::cout << "The list is empty!\n";
        else
         std::cout << "The list is not empty!\n";
        break;
      case -1:
        return 0;
      default:
        std::cout << "Invalid option! Please try a different value!" << std::endl;
        break;
    }
  }

  return 0;
}
