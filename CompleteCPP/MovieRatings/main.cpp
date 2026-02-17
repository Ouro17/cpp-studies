#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <vector>

static std::string toUpper(std::string value) {
  for (char &character : value) {
    character = static_cast<char>(std::toupper(character));
  }

  return value;
}

static int readNumber(const std::string &prompt) {
  int value = 0;

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

int main() {
  std::cout << "Welcome to the movie rating program." << std::endl;
  std::cout << "It allows you to score several movies." << std::endl;

  std::vector<std::string> titles;
  std::vector<int> ratings;

  const unsigned int TOTAL = 5;

  bool correctRating = false;
  std::string movieTitle = {};
  int rating = 0;

  for (unsigned int index = 0; index < TOTAL; index++) {

    std::cout << "Movie title: " << std::endl;
    std::getline(std::cin, movieTitle);

    do {
      rating = readNumber("Enter the score (from 0 to 10)");
      correctRating = rating >= 0 && rating <= 10;
      if (!correctRating) {
        std::cout << "Invalid value" << std::endl;
      }
    } while (!correctRating);

    titles.push_back(movieTitle);
    ratings.push_back(rating);
  }

  for (unsigned int index = 0; index < TOTAL; index++) {
    std::cout << "You rated " << titles[index] << " a " << ratings[index]
              << "/10" << std::endl;
  }

  return 0;
}
