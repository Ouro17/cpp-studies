#include "Exhibit.hpp"

Exhibit::Exhibit(std::string name, int roomNumber, double displaySize) {
    this->name = name;
    this->roomNumber = roomNumber;
    this->displaySize = displaySize;
}

std::string  Exhibit::getName() const { return this->name; }
int Exhibit::getRoomNumber() const { return this->roomNumber; }
double Exhibit::getDisplaySize() const { return this->displaySize; }