#include <cctype>
#include <ios>
#include <iostream>
#include <limits>
#include <string>

static std::string toUpper(std::string value) {
  for (char &character : value) {
    character = static_cast<char>(std::toupper(character));
  }

  return value;
}

static int readNumber(const std::string &prompt) {
  int year = 0;

  while (true) {
    std::cout << prompt << std::endl;

    if (std::cin >> year) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (year == 0) {
        std::cout << "Year 0 does not exist. Please enter a valid year."
                  << std::endl;
        continue;
      }

      return year;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Invalid input. Please enter a valid year." << std::endl;
  }
}

static void getTemperature(int &firstYear, int &secondYear) {
  firstYear = readNumber("Please enter the first year in range:");
  std::cout << "First year entered: " << firstYear << std::endl;

  do {
    secondYear = readNumber("Please enter the second year in range:");

    if (firstYear >= secondYear) {
      std::cout << "The second year must be greater than the first year."
                << std::endl;
    }

  } while (firstYear >= secondYear);

  std::cout << "First year entered: " << firstYear << std::endl;
  std::cout << "Second year entered: " << secondYear << std::endl;
}

static bool isLeapYear(int year) {
  if (year == 0) {
    return false;
  }

  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main() {
  const std::string LEAP = "leap";
  const std::string NOT_LEAP = "not leap";
  std::string confirmation;
  bool continueProgram = false;

  int firstYear = 0;
  int secondYear = 0;

  std::cout << "Welcome to the leap year checker" << std::endl;
  std::cout << "This program calculates the leap year for every year in a defined range." << std::endl;

  do {
    getTemperature(firstYear, secondYear);

    const unsigned int yearDifference = secondYear - firstYear;
    int currentYear = firstYear;

    std::cout << "There is : " << yearDifference << " years difference"
              << std::endl;
    std::cout << "Iterating years..." << std::endl;

    for (unsigned int index = 0; index < yearDifference; ++index) {
      std::string type = NOT_LEAP;

      if (isLeapYear(currentYear)) {
        type = LEAP;
      }

      std::cout << currentYear << " is " << type << " year." << std::endl;

      currentYear++;

      if (currentYear == 0) {
        currentYear++;
      }
    }

    std::cout << "Do you want to calculate another range? (Y/N):" << std::endl;
    std::getline(std::cin, confirmation);
    confirmation = toUpper(confirmation);
    continueProgram = confirmation == "Y";
  } while (continueProgram);

  return 0;
}
