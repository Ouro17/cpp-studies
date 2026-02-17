#include <iostream>
#include <ostream>
#include <string>
#include <vector>

static std::string toUpper(std::string value) {
  for (char &character : value) {
    character = static_cast<char>(std::toupper(character));
  }

  return value;
}

int main() {
  std::cout << "Welcome to the shopping list program." << std::endl;
  std::cout << "This program allows to create a shopping list." << std::endl;

  const auto DONE = "DONE";
  std::string currentValue = {};

  std::vector<std::string> values = {};
  bool finishProgram = false;

  do {
    std::cout << "Enter a item or 'done' to finish: " << std::endl;
    std::getline(std::cin, currentValue);
    finishProgram = toUpper(currentValue) == DONE;
    if (!finishProgram) {
      values.push_back(currentValue);
    }

  } while (!finishProgram);

  std::cout << "The list is " << std::endl;

  for (const std::string &value : values) {
    std::cout << "- " << value << std::endl;
  }

  return 0;
}
