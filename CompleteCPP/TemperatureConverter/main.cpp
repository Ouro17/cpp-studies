#include <array>
#include <iomanip>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>

enum class TemperatureScale { Celsius, Fahrenheit };

static std::string toUpper(std::string value) {
  for (char &character : value) {
    character = static_cast<char>(std::toupper(character));
  }

  return value;
}

static double readNumber(const std::string &prompt) {
  double value = 0.0;

  while (true) {
    std::cout << prompt << std::endl;

    if (std::cin >> value) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return value;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Invalid input. Please enter a valid number." << std::endl;
  }
}

static std::array<double, 7> getData() {
  std::array<double, 7> data = {};
  const auto total = data.size();

  for (unsigned int index = 0; index < total; ++index) {
    const auto value = readNumber("Please enter the value for day " +
                                  std::to_string(index + 1) + ":");
    data[index] = value;
  }

  return data;
}

double fahrenheitToCelsius(double fahrenheitDegrees) {
  return (fahrenheitDegrees - 32) * 5 / 9;
}

double celsiusToFahrenheit(double celsiusDegrees) {
  return (9 * celsiusDegrees + 160) / 5;
}

TemperatureScale getTemperatureType() {
  std::string value = {};
  auto correctData = false;
  do {
    std::cout << "Are the temperatures in (F)ahrenheit or in (C)elsius? (F/C)"
              << std::endl;
    std::getline(std::cin, value);
    value = toUpper(value);
    correctData = value == "F" || value == "C";

    if (!correctData) {
      std::cout << "The input is incorrect." << std::endl;
    }
  } while (!correctData);

  return value == "C" ? TemperatureScale::Celsius
                      : TemperatureScale::Fahrenheit;
}

bool getContinue() {
  std::string value = {};
  auto correctData = false;
  do {
    std::cout << "Do you want to calculate another range (Y/N)" << std::endl;
    std::getline(std::cin, value);
    value = toUpper(value);
    correctData = value == "Y" || value == "N";
  } while (!correctData);

  return value == "Y";
}

int main() {
  std::string confirmation;
  bool continueProgram = false;

  std::cout << "Welcome to the temperature converter" << std::endl;
  std::cout << "This program calculates the correspondent temperature in "
               "Fahrenheit to Celsius or the opposite."
            << std::endl;

  do {
    const auto temperatureScale = getTemperatureType();
    const auto type = temperatureScale == TemperatureScale::Celsius ? "C" : "F";
    const auto otherType = temperatureScale == TemperatureScale::Celsius ? "F" : "C";
    const auto data = getData();

    const auto totalSize = data.size();

    const auto convertToOtherType =
        temperatureScale == TemperatureScale::Celsius ? fahrenheitToCelsius : celsiusToFahrenheit;

    // Configure the cout
    std::cout << std::fixed << std::setprecision(2);

    for (unsigned int index = 0; index < totalSize; ++index) {
      std::cout << "The temperature for day " << index + 1 << " is "
                << data[index] << "º" << type << " and "
                << convertToOtherType(data[index]) << "º" << otherType
                << std::endl;
    }

    continueProgram = getContinue();
  } while (continueProgram);

  return 0;
}
