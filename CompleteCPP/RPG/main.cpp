#include "Archer.hpp"
#include "Warrior.hpp"
#include "Wizard.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

static int readInteger(std::string_view prompt) {
  int number = 0;

  while (true) {
    std::cout << prompt << std::endl;

    if (std::cin >> number) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (number < 0) {
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

static std::string readString(std::string_view prompt) {
  std::string value;
  std::cout << prompt << std::endl;
  std::getline(std::cin, value);
  return value;
}

static std::string toLower(std::string value) {
  for (char &character : value) {
    character = static_cast<char>(std::tolower(character));
  }

  return value;
}

static std::string toUpper(std::string value) {
  for (char &character : value) {
    character = static_cast<char>(std::toupper(character));
  }

  return value;
}

static Race readRace(std::string_view prompt) {
  return to_race(toLower(readString(prompt)));
}

static bool checkContinue(std::string_view prompt) {
  return toUpper(readString(prompt)) == "Y";
}

static int readClass(std::string_view prompt) {
  std::cout << "Warrior (1), Archer (2), Wizard (3): " << std::endl;
  return readInteger(prompt);
}

static Player *readAndCreatePlayer() {
  auto name = readString("Write the name: ");
  auto race = readRace("What is the race? ");
  auto player_class = readClass("What is the class?");

  switch (player_class) {
  case 2:
    return new Archer(name, race);
  case 3:
    return new Wizard(name, race);
  default:
    return new Warrior(name, race);
  }
}

static void showPlayers(const std::vector<Player *> data) {
  auto current = 1u;
  for (auto element : data) {
    std::cout << current << " -- "
              << "Name: " << element->getName()
              << ", Race: " << to_string(element->getRace())
              << ", Hit/Magic points: " << element->getHitPoints() << " / "
              << element->getMagicPoints()
              << ", Attack: "<< element->attack() << std::endl;

    current++;
  }
}

static void deleteElements(std::vector<Player *> data) {
  for (auto element : data) {
    delete element;
  }

  data.clear();
}

int main() {
  auto continueProgram = false;

  std::cout << "Welcome to the RPG character creation program" << std::endl;
  std::cout << "This program allows to create and store RPG players"
            << std::endl;

  do {
    std::vector<Player *> players;

    auto continueCreating = false;

    do {
      const auto newPlayer = readAndCreatePlayer();

      if (newPlayer != nullptr) {
        players.push_back(newPlayer);
      }

      continueCreating = checkContinue("Do you want to another player? (Y/N)");
    } while (continueCreating);

    showPlayers(players);

    deleteElements(players);

    continueProgram = checkContinue("Do you want to start over? (Y/N):");
  } while (continueProgram);

  return EXIT_SUCCESS;
}