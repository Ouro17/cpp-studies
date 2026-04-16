#include "Exhibit.hpp"

Exhibit::Exhibit(const std::string name, const int roomNumber, const double displaySize) {
    this->name = name;
    this->roomNumber = roomNumber;
    this->displaySize = displaySize;
}

std::string  Exhibit::getName() const { return this->name; }
int Exhibit::getRoomNumber() const { return this->roomNumber; }
double Exhibit::getDisplaySize() const { return this->displaySize; }