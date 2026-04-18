#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <vector>

#include "Student.hpp"

int main() {
  std::cout << "Welcome to the Student Roster program" << std::endl;
  std::cout << "This program will read and calculate some statistics about the "
               "students.txt file"
            << std::endl;

  auto inputFile = std::ifstream("students.txt");

  if (!inputFile) {
    std::cerr << "Error opening the file. Exiting program...";
    return EXIT_FAILURE;
  }

  const auto MIN_GPA_FOR_HONORS = 3.5;
  const auto MIN_VALID_GPA = 0;
  const auto MAX_VALID_GPA = 4;

  auto averageGPA = 0.0;
  auto sumOfAllGPA = 0.0;
  auto totalStudents = 0u;
  auto studentsWithHonors = 0u;

  std::vector<Student *> students;

  std::string firstName;
  std::string lastName;
  double GPA;

  while (inputFile >> firstName >> lastName >> GPA) {

    if (GPA < MIN_VALID_GPA || GPA > MAX_VALID_GPA || firstName.empty() ||
        lastName.empty()) {
      continue;
    }

    totalStudents++;
    sumOfAllGPA += GPA;

    if (GPA > MIN_GPA_FOR_HONORS) {
      studentsWithHonors++;
    }

    students.push_back(new Student(firstName, lastName, GPA));
  }

  inputFile.close();

  if (totalStudents > 0) {
    averageGPA = sumOfAllGPA / totalStudents;
  }

  std::cout << "Number of valid students is: " << totalStudents << std::endl;
  std::cout << "Average GPA: " << averageGPA << std::endl;
  std::cout << "Honor students: " << studentsWithHonors << std::endl;

  std::cout << "Students: " << std::endl;
  std::cout << "--------------------------" << std::endl;

  for (Student *student : students) {
    std::cout << student->getFirstName() << " " << student->getLastName()
              << " GPA: " << student->getGPA() << std::endl;

    delete student;
  }

  students.clear();

  return EXIT_SUCCESS;
}