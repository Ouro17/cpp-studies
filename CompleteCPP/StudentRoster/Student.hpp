#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
  Student(std::string firstName, std::string lastName, double GPA);

  std::string getFirstName() const;
  std::string getLastName() const;
  double getGPA() const;

private:
  std::string firstName;
  std::string lastName;
  double GPA;
};

#endif