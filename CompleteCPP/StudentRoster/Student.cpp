#include "Student.hpp"

Student::Student(std::string firstName, std::string lastName, double GPA){
    this->firstName = firstName;
    this->lastName = lastName;
    this->GPA = GPA;
}

std::string Student::getFirstName() const { return firstName; }

std::string Student::getLastName() const { return lastName; }

double Student::getGPA() const { return GPA; }