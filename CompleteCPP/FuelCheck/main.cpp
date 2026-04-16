#include "FuelLevelCritical.hpp"
#include <cctype>
#include <iostream>
#include <ostream>
#include <string>

static std::string toUpper(std::string value) {
  for (char &character : value) {
    character = static_cast<char>(std::toupper(character));
  }

  return value;
}

static bool checkContinue(const std::string &prompt) {
  std::string confirmation;
  std::cout << prompt << std::endl;
  std::getline(std::cin, confirmation);
  return toUpper(confirmation) == "Y";
}

static void checkFuel(int currentFuelPercentage) {
  if (currentFuelPercentage <= 5) {
    throw FuelLevelCritical();
  }

  if (currentFuelPercentage <=10) {
    throw FuelLevelCritical("The fuel is getting low, please refuel soon. Remaining is "  + std::to_string(currentFuelPercentage) + "%");
  }
}

int main() {
  bool continueProgram = false;

  std::cout << "Welcome to the fuel checker" << std::endl;
  std::cout << "This program will check the fuel constantly and give an error "
               "when it's critical"
            << std::endl;

  do {
    for (int currentFuelPercentage = 100; currentFuelPercentage > 0;
         currentFuelPercentage -= 5) {
      try {
        checkFuel(currentFuelPercentage);
        std::cout << "Levels are normal, fuel remaining: " << currentFuelPercentage << "%" << std::endl;
      } catch (const FuelLevelCritical &err) {
        std::cerr << "Exception: " << err.what() << std::endl;
      }
    }

    continueProgram = checkContinue("Do you want to try again? (Y/N):");
  } while (continueProgram);

  return EXIT_SUCCESS;
}
