#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>

int main() {
  std::cout << "Welcome to the employee salary report" << std::endl;
  std::cout
      << "This program calculates some statistics about the salary.txt file"
      << std::endl;

  auto inputFile = std::ifstream("salary.txt");

  if (!inputFile) {
    std::cerr << "Error opening the file. Exiting program...";
    return EXIT_FAILURE;
  }

  const auto MIN_VALID_SALARY = 0.0;
  const auto MAX_VALID_SALARY = 1000000.0;

  auto averageSalary = 0.0;
  auto totalSumSalaries = 0.0;
  auto employeesWithMoreThan100kInSalary = 0;
  auto numberOfEmployees = 0;

  auto readNumber = 0.0;
  while (inputFile >> readNumber) {

    if (readNumber < MIN_VALID_SALARY || readNumber > MAX_VALID_SALARY) {
      continue;
    }

    numberOfEmployees++;
    totalSumSalaries += readNumber;

    if (readNumber > 100000.0) {
      employeesWithMoreThan100kInSalary++;
    }
  }

  inputFile.close();

  if (numberOfEmployees > 0) {
    averageSalary = totalSumSalaries / numberOfEmployees;
  }

  std::cout << "Number of employees is: " << numberOfEmployees << std::endl;
  std::cout << "Total salary payroll is: " << totalSumSalaries << std::endl;
  std::cout << "Average salary is: " << averageSalary << std::endl;
  std::cout << "Employees with more than a 100k in salary is: "
            << employeesWithMoreThan100kInSalary << std::endl;

  return EXIT_SUCCESS;
}