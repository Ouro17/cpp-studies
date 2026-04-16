#include "Drone.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
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

static int readInteger(const std::string &prompt) {
  int number = 0;

  while (true) {
    std::cout << prompt << std::endl;

    if (std::cin >> number) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (number < 1) {
        std::cout << "Can't read less than 1." << std::endl;
        continue;
      }

      return number;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Invalid input. Please enter a valid number." << std::endl;
  }
}

static double readDouble(const std::string &prompt) {
  double number = 0;

  while (true) {
    std::cout << prompt << std::endl;

    if (std::cin >> number) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (number < 0.0) {
        std::cout << "Can't read less than 0." << std::endl;
        continue;
      }

      return number;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Invalid input. Please enter a valid number." << std::endl;
  }
}

static std::string readString(const std::string &prompt) {
  std::string value;
  std::cout << prompt << std::endl;
  std::getline(std::cin, value);
  return value;
}

static Drone *readAndCreateDrone() {
  const auto modelName = readString("Enter the model name: ");
  const double batteryLife = readDouble("Enter the battery life: ");

  return new Drone(modelName, batteryLife);
}

static void showDrones(const Drone *const *drones, const int capacity) {
  std::cout << "Drones created: " << std::endl;

  for (auto index = 0u; index < capacity; index++) {
    const auto temp = drones[index];

    if (temp == nullptr) {
      continue;
    }

    std::cout << "Model name: " << temp->getModelName() << std::endl;
    std::cout << "Battery Life: " << temp->getBatteryLife() << std::endl;
    std::cout << "------------------------------------" << std::endl;
  }
}

static void deleteDrones(Drone **drones, const int capacity) {
  for (auto index = 0u; index < capacity; index++) {
    delete drones[index];
    drones[index] = nullptr;
  }

  delete[] drones;
}

int main() {
  auto continueProgram = false;

  std::cout << "Welcome to the dynamic drone" << std::endl;
  std::cout << "This program stores dynamically drones" << std::endl;

  do {
    auto currentDroneQuantity = 0u;
    const auto maxDroneQuantity =
        readInteger("How many drones do you want to store?");

    auto drones = new Drone *[maxDroneQuantity]();
    auto continueCreating = false;

    do {

      if (currentDroneQuantity >= maxDroneQuantity) {
        std::cout << "Drones storage capacity reached." << std::endl;
        break;
      }

      const auto newDrone = readAndCreateDrone();

      if (newDrone != nullptr) {
        drones[currentDroneQuantity] = newDrone;
        currentDroneQuantity++;
      }

      continueCreating = checkContinue("Do you want to another drone? (Y/N)");
    } while (continueCreating);

    showDrones(drones, currentDroneQuantity);

    deleteDrones(drones, currentDroneQuantity);
    drones = nullptr;

    continueProgram = checkContinue("Do you want to start over? (Y/N):");
  } while (continueProgram);

  return EXIT_SUCCESS;
}
