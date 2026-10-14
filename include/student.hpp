#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <chrono>

class student {
private:
  std::string m_first_name;
  std::string m_last_name;
  std::string m_m_number;
  float m_gpa;
  std::chrono::year_month_day m_birthday;

public:
  student(std::string first_name, std::string last_name, std::string m_number, std::chrono::year_month_day birthday, float gpa)
  {
    m_first_name = first_name;
    m_last_name = last_name;
    m_m_number = m_number;
    m_gpa = gpa;
    m_birthday = birthday;
  }

// chrono example
// std::chrono::year_month_day today = std::chrono::year{2026} / std::chrono::October / 7d;

  std::string get_name()
  {
    return m_first_name + " " + m_last_name;
  }

  std::string get_m_number()
  {
    return m_m_number;
  }
  int get_age();
  bool operator<(const student& other);
  bool operator>(const student& other);
  bool operator==(const student& other);
  
};


#endif
