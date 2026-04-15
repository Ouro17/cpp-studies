#include <cctype>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <stdexcept>
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

static int readNumber(const std::string &prompt) {
  int number = 0;

  while (true) {
    std::cout << prompt << std::endl;

    if (std::cin >> number) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return number;
  }

  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "Invalid input. Please enter a valid number." << std::endl;
}

static std::string getMonthName(int monthNumber) {

  switch (monthNumber) {
  case 1:
    return "January";
  case 2:
    return "February";
  case 3:
    return "March";
  case 4:
    return "April";
  case 5:
    return "May";
  case 6:
    return "June";
  case 7:
    return "July";
  case 8:
    return "August";
  case 9:
    return "September";
  case 10:
    return "October";
  case 11:
    return "November";
  case 12:
    return "December";
  default:
    throw std::out_of_range("Month must be between 1 and 12");
  }
}

int main() {
  bool continueProgram = false;

  int monthNumber = 0;

  std::cout << "Welcome to the month speller" << std::endl;
  std::cout << "This program spells the month for a given number" << std::endl;

  do {
    try {
      monthNumber = readNumber("What month number do you want to spell?");
      getMonthName(monthNumber);
    } catch (const std::out_of_range &err) {
      std::cerr << "Exception: " << err.what() << std::endl;
    }
    continueProgram =
        checkContinue("Do you want to spell months again? (Y/N):");
  } while (continueProgram);

  return 0;
}
