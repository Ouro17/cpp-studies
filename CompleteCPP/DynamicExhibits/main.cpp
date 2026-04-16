#include "Exhibit.hpp"
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

int main() {
  bool continueProgram = false;
  std::cout << "Welcome to the dynamic exhibit" << std::endl;
  std::cout << "This program stores dynamically 3 exhibits but the array is for 4"
            << std::endl;

    const int COUNT = 4;

    Exhibit *exhibits[COUNT] = {};

    Exhibit *one = new Exhibit("First", 0, 20.0);
    Exhibit *two = new Exhibit("Second", 1, 10.0);
    Exhibit *three = new Exhibit("Third", 2, 5.0);

    exhibits[0] = one;
    exhibits[1] = two;
    exhibits[2] = three;

    for (int index = 0; index < COUNT; index++) {
      Exhibit *temp = exhibits[index];

      if (temp == nullptr) {
        continue;
      }

      std::cout << "Name: " << temp->getName() << std::endl;
      std::cout << "Room Number: " << temp->getRoomNumber() << std::endl;
      std::cout << "Display Size: " << temp->getDisplaySize() << std::endl;
    }

    for (int index = 0; index < COUNT; index++) {
      delete exhibits[index];
      exhibits[index] = nullptr;
    }

  return EXIT_SUCCESS;
}
