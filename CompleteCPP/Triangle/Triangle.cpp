#include "Triangle.hpp"
#include <cmath>
#include <iostream>
#include <ostream>

Triangle::Triangle() {}

Triangle::Triangle(double sideA, double sideB, double sideC) {
  this->sideA = sideA;
  this->sideB = sideB;
  this->sideC = sideC;
}

double Triangle::getSideA() const { return this->sideA; }

double Triangle::getSideB() const { return this->sideB; }

double Triangle::getSideC() const { return this->sideC; }

void Triangle::setSideA(double newValue) { this->sideA = newValue; }

void Triangle::setSideB(double newValue) { this->sideB = newValue; }

void Triangle::setSideC(double newValue) { this->sideC = newValue; }

bool Triangle::isValid() const {
  return ((sideA + sideB) > sideC) && ((sideA + sideC) > sideB) &&
         ((sideB + sideC) > sideA);
}

double Triangle::perimeter() const { return sideA + sideB + sideC; }

double Triangle::area() const {
  if (!isValid()) {
    return 0.0;
  }

  const auto s = perimeter() / 2.0;

  return std::sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
}

void Triangle::print() const {
  std::cout << "Sides (" << sideA << " , " << sideB << " , " << sideC << ")"
            << std::endl;

  std::cout << "Is valid? " << isValid() << std::endl;
  std::cout << "Perimeter " << perimeter() << std::endl;
  std::cout << "Area " << area() << std::endl;
}
