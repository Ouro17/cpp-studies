#include "RpsConstants.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct RandomSelector {
  std::mt19937 engine;
  std::uniform_int_distribution<size_t> distr;

  RandomSelector(std::mt19937::result_type seed = std::random_device{}())
      : engine(seed), distr(0, 0) {}

  void setRange(size_t max) {
    distr.param(std::uniform_int_distribution<size_t>::param_type(0, max - 1));
  }

  size_t operator()() { return distr(engine); }
};

static std::string toUpper(std::string value) {
  for (char &character : value) {
    character = static_cast<char>(std::toupper(character));
  }

  return value;
}

static bool isValidOption(const std::string &option,
                          const std::vector<std::string> options) {
  return std::find(options.begin(), options.end(), option) != options.end();
}

static std::string randomOption(const std::vector<std::string> &options,
                                RandomSelector &randomSelector) {
  if (options.empty()) {
    return {};
  }

  return options[randomSelector()];
}

using WinRules =
    std::unordered_map<std::string, std::unordered_set<std::string>>;

static bool isWin(const std::string &option1, const std::string &option2) {
  static const WinRules winRules = {{Rps::Rock, {Rps::Scissors}},
                                    {Rps::Paper, {Rps::Rock}},
                                    {Rps::Scissors, {Rps::Paper}}};

  const auto ruleIterator = winRules.find(option1);

  if (ruleIterator == winRules.end()) {
    return false;
  }

  return ruleIterator->second.find(option2) != ruleIterator->second.end();
}

int main() {
  const auto TIE = "That is a tie!";
  const auto YOU_WIN = "You win!";
  const auto YOU_LOSE = "You lose!";
  const auto TRY_AGAIN = "Try again";

  const auto options = {Rps::Rock, Rps::Paper, Rps::Scissors};

  RandomSelector randomSelector;
  randomSelector.setRange(options.size());

  std::string confirmation;
  bool continueProgram = false;

  std::cout << "Welcome to the game Rock, Paper, Pleas.. Sorry, I meant "
               "Scissors."
            << std::endl;

  std::cout << "(Can't shake the habit yet...)" << std::endl;

  std::cout << "You know the drill: Choose one option R(ock), P(aper), "
               "S(cissors) to play"
            << std::endl;

  std::cout << "and the machine will randomly choose another one to play."
            << std::endl;

  std::cout << "Good luck!" << std::endl;

  std::string playerPlay;

  do {
    bool valid = false;

    do {
      std::cout << "What will you play?" << std::endl;
      std::cout << "Choose one option R(ock), P(aper), "
                   "S(cissors):"
                << std::endl;

      std::getline(std::cin, playerPlay);

      playerPlay = toUpper(playerPlay);

      valid = isValidOption(playerPlay, options);

      if (!valid) {
        std::cout << "WhOha, that was not an option!" << std::endl;
      }

    } while (!valid);

    std::string machinePlay = randomOption(options, randomSelector);

    std::cout << "You played " << playerPlay << " and machine played "
              << machinePlay << std::endl;

    if (machinePlay == playerPlay) {
      std::cout << TIE << std::endl;
    } else if (isWin(playerPlay, machinePlay)) {
      std::cout << YOU_WIN << std::endl;
    } else if (isWin(machinePlay, playerPlay)) {
      std::cout << YOU_LOSE << std::endl;
      std::cout << TRY_AGAIN << std::endl;
    }

    std::cout << "Do you want to play again? (Y/N):" << std::endl;
    std::getline(std::cin, confirmation);
    confirmation = toUpper(confirmation);
    continueProgram = confirmation == "Y";
  } while (continueProgram);

  return 0;
}
