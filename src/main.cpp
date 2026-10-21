#include <include/ordered_linked_list.hpp>
#include <include/student.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <chrono>

bool save_to_file(const std::string& filename, ordered_linked_list<student>& l);
bool load_from_file(const std::string& filename, ordered_linked_list<student>& l);

student* create_student(ordered_linked_list<student>& l);


int main()
{
  std::cout << "Task 7 Student Database!\n";
  ordered_linked_list<student> l;

  while (true)
  {
    std::cout << "\n -- Menu -- \n"
      << " [1] Add Student\n"
      << " [2] Get Student\n"
      << " [3] Search For Student\n"
      << " [4] Display All Students\n"
      << " [5] Display Student At Index\n"
      << " [6] Remove All Students\n"
      << " [7] Save Students To File\n"
      << " [8] Load Students From File\n"
      << " [9] Display Smallest M Number\n"
      << " [10] Display Largest M Number\n"
      << " [11] Reverse List\n"
      << " [12] Exit\n"
      << "Select an option: ";

    int value;
    std::cin >> value;

    switch(value)
    {
      case 1:
        {
          student* created_student = create_student(l);
          if (created_student)
          {
            l.add_item(created_student);
            std::cout << "Student added to list!\n";
          }
        }
        break;
      case 2:
        {
          std::cout << "Enter an MNumber to get and remove from the list: ";
          std::string m_number;
          std::cin >> m_number;

          student* dummy_student = new student("", "", m_number, std::chrono::year(2000)/1/1);
          student* found_student = l.get_item(dummy_student);

          if (found_student)
          {
            std::cout << "Student " << found_student->get_name() << " was removed from the list!\n";
            delete found_student;
          }
          else std::cout << "Student was not found in the list!\n";
          delete dummy_student;
        }
        break;
      case 3:
        {
          std::cout << "Enter an MNumber to search for: ";
          std::string m_number;
          std::cin >> m_number;
          student* dummy_student = new student("", "", m_number, std::chrono::year(2000)/1/1);

          if (l.is_in_list(dummy_student))
            std::cout << "Student is in the list!\n";
          else 
            std::cout << "Student is not in the list!\n";
          delete dummy_student;
        }
        break;
      case 4:
        l.display_all();
        break;
      case 5:
        {
          std::cout << "Which index? ";
          int index;
          std::cin >> index;
          try {
            student* current_student = l.see_at(index);
            if (current_student)
              current_student->display();

          }
          catch (std::out_of_range e) {
            std::cout << "Error: " << e.what() << std::endl;
          }
        }
        break;
      case 6:
        l.remove_all();
        std::cout << "All students removed!\n";
        break;
      case 7:
        {
          std::cout << "Enter a filename to save to: ";
          std::string filename;
          std::cin >> filename;
          save_to_file(filename, l);
        }
        break;
      case 8:
        {
          std::cout << "Enter a filename to load from: ";
          std::string filename;
          std::cin >> filename;
          load_from_file(filename, l);
        }
        break;
      case 9:
        {
          student* smallest = l.get_smallest();
          if (smallest)
          {
            std::cout << "Smallest M Number in the linked list: \n";
            smallest->display();
          }
          else std::cout << "The list is empty!\n";
        }
        break;
      case 10:
        {
          student* largest = l.get_largest();
          if (largest)
          {
            std::cout << "Largest M Number in the linked list: \n";
            largest->display();
          }
          else std::cout << "The list is empty!\n";
        }
        break;
      case 11:
        l.reverse();
        std::cout << "List has been reversed! Try displaying the list to see!\n";
        break;
      case 12:
        std::cout << "Exiting...\n";
        return 0;
      default:
        std::cout << "Invalid option! Please try a different value!\n";
        break;
    }
  }


  return 0;
}

student* create_student(ordered_linked_list<student>& l)
{
  std::string first_name, last_name, m_number;
  int birth_year, birth_month, birth_day;
  float gpa;

  std::cout << "Please enter the student's first name: ";
  std::cin >> first_name;
  if (first_name.empty()) { std::cout << "Error: First name cannot be empty.\n"; return nullptr; }

  std::cout << "Please enter the student's last name: ";
  std::cin >> last_name;
  if (last_name.empty()) { std::cout << "Error: Last name cannot be empty.\n"; return nullptr; }

  std::cout << "Please enter the student's M Number (in format M12345678): ";
  std::cin >> m_number;
  if (m_number.empty() || m_number[0] != 'M') { std::cout << "Error: Invalid M Number format.\n"; return nullptr; }

  student* dummy = new student("", "", m_number, std::chrono::year(2000)/1/1);
  if (l.is_in_list(dummy)) {
      std::cout << "Error: A student with " << m_number << " already exists. Student was not added.\n";
      delete dummy;
      return nullptr;
  }
  delete dummy;

  std::cout << "Please enter the student's birth year: ";
  std::cin >> birth_year;
  std::cout << "Please enter the student's birth month (1-12): ";
  std::cin >> birth_month;
  std::cout << "Please enter the student's birth day (1-31): ";
  std::cin >> birth_day;

  if (birth_month < 1 || birth_month > 12 || birth_day < 1 || birth_day > 31) {
      std::cout << "Error: Invalid birthday.\n";
      return nullptr;
  }
  
  std::chrono::year_month_day date_of_birth(std::chrono::year(birth_year) / std::chrono::month(birth_month) / std::chrono::day(birth_day));
  
  auto today = std::chrono::year_month_day{std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
  if (date_of_birth > today) {
      std::cout << "Error: Future birthday is not allowed.\n";
      return nullptr;
  }

  std::cout << "Please enter a gpa (0.0 to 4.0): ";
  std::cin >> gpa;
  
  if (gpa < 0.0 || gpa > 4.0) {
      std::cout << "Error: Invalid GPA. Must be between 0.0 and 4.0.\n";
      return nullptr;
  }

  return new student(first_name, last_name, m_number, date_of_birth, gpa);
}

bool save_to_file(const std::string& filename, ordered_linked_list<student>& l)
{
  std::ofstream out(filename);

  if (!out.is_open())
  {
    std::cout << "Error: unable to open file for saving!\n";
    return false;
  }

  out << l.size() << "\n";

  for (auto it = l.begin(); it != l.end(); ++it)
  {
    student* s = *it;

    out << s->get_first_name() << "\n"
        << s->get_last_name() << "\n"
        << s->get_m_number() << "\n"
        << (int)s->get_date_of_birth().year() << "\n"
        << (unsigned)s->get_date_of_birth().month() << "\n"
        << (unsigned)s->get_date_of_birth().day() << "\n"
        << s->get_gpa() << "\n" ;
  }

  out.close();
  std::cout << "Successfully saved to " << filename << "!\n";
  return true;
}

bool load_from_file(const std::string& filename, ordered_linked_list<student>& l)
{
  std::ifstream in(filename);

  if (!in.is_open())
  {
    std::cout << "Error: unable to open file " << filename << "!\n";
    return false;
  }

  l.remove_all();

  int size;
  if (!(in >> size)) return false;

  for (int i = 0; i < size; ++i)
  {
    std::string first, last, m_number;
    int year, month, day;
    float gpa;

    in >> first >> last >> m_number >> year >> month >> day >> gpa;

    std::chrono::year_month_day date_of_birth(std::chrono::year(year) / std::chrono::month(month) / std::chrono::day(day));
    student* retrieved_student = new student(first, last, m_number, date_of_birth, gpa);
    l.add_item(retrieved_student);
  }

  in.close();
  std::cout << "Successfully loaded " << size << " students from " << filename << "!\n";
  return true;
}
