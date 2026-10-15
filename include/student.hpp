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
  student(std::string first_name, std::string last_name, std::string m_number, std::chrono::year_month_day birthday, float gpa = 0.f)
  {
    m_first_name = first_name;
    m_last_name = last_name;
    m_m_number = m_number;
    m_gpa = gpa;
    m_birthday = birthday;
  }

  student(student&&) = delete;

  std::string get_name() const
  {
    return m_first_name + " " + m_last_name;
  }

  std::string get_m_number() const
  {
    return m_m_number;
  }

  int get_age() const
  {
    // get today
    std::chrono::year_month_day today{std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};

    // get years
    std::chrono::years age = today.year() - m_birthday.year();

    // subtract 1 year if birthday hasn't happened yet this year
    if (std::chrono::month_day{today.month(), today.day()} < std::chrono::month_day{m_birthday.month(), m_birthday.day()}) {
        age -= std::chrono::years{1};
    }

    // return age as int
    return age.count();
  }
  bool operator<(const student& other) const
  {
    return m_m_number < other.get_m_number();
  }
  bool operator>(const student& other) const
  {
    return m_m_number > other.get_m_number();
  }

  bool operator==(const student& other) const
  {
    return m_m_number == other.get_m_number();
  }
  
};


#endif
