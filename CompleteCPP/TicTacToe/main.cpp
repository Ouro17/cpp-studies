#include <cctype>
#include <iostream>
#include <ostream>
#include <random>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

enum class Player { XPlayer, OPlayer, Tie };
enum class PlayMode { Machine, Player };
constexpr char X_PIECE = 'X';
constexpr char O_PIECE = 'O';
constexpr char EMPTY_PIECE = ' ';

static std::string toUpper(std::string value) {
  for (char &character : value) {
    character = static_cast<char>(std::toupper(character));
  }

  return value;
}

static PlayMode getPlayMode() {
  const std::string PLAYER = "P";
  const std::string MACHINE = "M";
  std::string line;
  auto correctData = false;
  do {
    std::cout << "Which mode do you want to play (P)layer or (M)achine? ("
              << PLAYER << "/" << MACHINE << ")" << std::endl;
    if (!std::getline(std::cin, line)) {
      std::cout << "Input interrupted." << std::endl;
      std::exit(EXIT_SUCCESS);
    }
    line = toUpper(line);
    correctData = line == PLAYER || line == MACHINE;
  } while (!correctData);

  return line == PLAYER ? PlayMode::Player : PlayMode::Machine;
}

static unsigned int getBoardSize() {
  constexpr unsigned int MIN_BOARD_SIZE = 2;

  while (true) {
    std::cout << "What will be the board size? (Number greater than 1)"
              << std::endl;

    std::string line;
    if (!std::getline(std::cin, line)) {
      std::cout << "Input interrupted." << std::endl;
      std::exit(EXIT_SUCCESS);
    }

    std::istringstream stream(line);
    int temp;
    char extra;

    // Read exactly one integer and discard the rest
    if (!(stream >> temp) || (stream >> extra)) {
      std::cout << "Invalid input." << std::endl;
      continue;
    }

    if (temp < static_cast<int>(MIN_BOARD_SIZE)) {
      std::cout << "The number needs to be greater than 1." << std::endl;
      continue;
    }

    return static_cast<unsigned int>(temp);
  }
}

static bool askContinue() {
  const std::string YES = "Y";
  const std::string NO = "N";
  std::string line;
  auto correctData = false;
  do {
    std::cout << "Do you want to play again? (" << YES << "/" << NO << ")"
              << std::endl;
    if (!std::getline(std::cin, line)) {
      std::cout << "Input interrupted." << std::endl;
      std::exit(EXIT_SUCCESS);
    }

    line = toUpper(line);
    correctData = line == YES || line == NO;
  } while (!correctData);

  return line == YES;
}

void getNumbersSeparatedBySpace(unsigned int &row, unsigned int &column,
                                const unsigned int boardSize) {
  while (true) {
    std::cout << "Enter row and column (0 to " << boardSize - 1
              << "), separated by space:" << std::endl;

    std::string line;
    if (!std::getline(std::cin, line)) {
      std::cout << "Input interrupted." << std::endl;
      std::exit(EXIT_SUCCESS);
    }

    std::istringstream stream(line);
    std::string token;
    unsigned int values[2];
    auto count = 0u;
    auto valid = true;

    while (stream >> token) {
      if (count >= 2u) {
        valid = false;
        break;
      }

      try {
        auto parsed = std::stoul(token);
        if (parsed >= boardSize) {
          valid = false;
          break;
        }
        values[count] = static_cast<unsigned int>(parsed);
      } catch (...) {
        valid = false;
        break;
      }

      ++count;
    }

    if (valid && count == 2u) {
      row = values[0];
      column = values[1];
      return;
    }

    std::cout << "Bad numbers, try again." << std::endl;
  }
}

static void getPosition(const std::vector<char> &data,
                        const unsigned int boardSize, unsigned int &row,
                        unsigned int &column) {
  auto positionTaken = true;
  do {
    getNumbersSeparatedBySpace(row, column, boardSize);

    // If position are already taken, retry
    positionTaken = data[row * boardSize + column] != EMPTY_PIECE;
    if (positionTaken) {
      std::cout << "That position is already taken, choose another."
                << std::endl;
    }
  } while (positionTaken);
}

static void drawSeparators(const unsigned int boardSize) {
  for (auto index = 0u; index < boardSize; ++index) {
    std::cout << "---";
  }

  std::cout << "-" << std::endl;
}

static void drawBoard(const std::vector<char> &data,
                      const unsigned int boardSize) {

  auto lastIndex = boardSize - 1u;

  std::cout << "  ";

  for (auto row = 0u; row < boardSize; ++row) {
    std::cout << ' ' << row;
  }
  std::cout << std::endl;

  drawSeparators(boardSize);

  for (auto row = 0u; row < boardSize; ++row) {
    std::cout << row << ' ';

    for (auto column = 0u; column < boardSize; ++column) {
      auto value = data[row * boardSize + column];

      std::cout << '|' << value;

      if (column == lastIndex) {
        std::cout << '|' << std::endl;
      }
    }

    drawSeparators(boardSize);
  }
}

constexpr Player pieceToPlayer(char piece) {
  return piece == X_PIECE ? Player::XPlayer : Player::OPlayer;
}

constexpr char playerToPiece(Player player) {
  return player == Player::XPlayer ? X_PIECE : O_PIECE;
}

static bool checkLine(const std::vector<char> &data, unsigned int startIndex,
                      unsigned int step, unsigned int boardSize,
                      char &winningPiece) {
  const char firstPiece = data[startIndex];

  for (auto offset = 1u; offset < boardSize; ++offset) {
    const auto index = startIndex + offset * step;
    const auto currentPiece = data[index];

    if (currentPiece == EMPTY_PIECE || currentPiece != firstPiece) {
      return false;
    }
  }

  winningPiece = firstPiece;
  return true;
}

static bool checkVictory(const std::vector<char> &data,
                         const unsigned int boardSize, Player &victoryPlayer) {
  const auto boardFull = std::all_of(
      data.begin(), data.end(), [](char cell) { return cell != EMPTY_PIECE; });

  if (boardFull) {
    victoryPlayer = Player::Tie;
    return true;
  }

  char winningPiece = EMPTY_PIECE;

  // Rows
  for (auto row = 0u; row < boardSize; ++row) {
    const auto startIndex = row * boardSize;
    const auto step = 1u;

    if (checkLine(data, startIndex, step, boardSize, winningPiece)) {
      victoryPlayer = pieceToPlayer(winningPiece);
      return true;
    }
  }

  // Columns
  for (auto column = 0u; column < boardSize; ++column) {
    const auto startIndex = column;
    const auto step = boardSize;

    if (checkLine(data, startIndex, step, boardSize, winningPiece)) {
      victoryPlayer = pieceToPlayer(winningPiece);
      return true;
    }
  }

  // Top-left diagonal to bottom-right
  {
    const auto startIndex = 0u;
    const auto step = boardSize + 1u;

    if (checkLine(data, startIndex, step, boardSize, winningPiece)) {
      victoryPlayer = pieceToPlayer(winningPiece);
      return true;
    }
  }

  // Top-right diagonal to bottom-left
  {
    const auto startIndex = boardSize - 1u;
    const auto step = boardSize - 1u;

    if (checkLine(data, startIndex, step, boardSize, winningPiece)) {
      victoryPlayer = pieceToPlayer(winningPiece);
      return true;
    }
  }

  return false;
}

constexpr Player nextPlayer(const Player current) {
  return current == Player::XPlayer ? Player::OPlayer : Player::XPlayer;
}

constexpr void indexToPosition(const unsigned int index,
                               const unsigned int boardSize, unsigned int &row,
                               unsigned int &column) {
  row = index / boardSize;
  column = index % boardSize;
}

static void machinePlay(const std::vector<char> &data,
                        const unsigned int boardSize, unsigned int &row,
                        unsigned int &column) {

  auto emptyCount = 0u;

  for (const auto cell : data) {
    if (cell == EMPTY_PIECE) {
      ++emptyCount;
    }
  }

  // Board is full, should not happen if code is correct
  if (emptyCount == 0u) {
    return;
  }

  static std::mt19937 engine{std::random_device{}()};
  std::uniform_int_distribution<unsigned int> dist(0, emptyCount - 1);

  auto target = dist(engine);

  // Iterate the board until finding an empty space
  // Then counting down until the empty space that we want
  // This is done to avoid allocations
  for (auto index = 0u; index < data.size(); ++index) {
    if (data[index] == EMPTY_PIECE) {
      if (target == 0) {
        indexToPosition(index, boardSize, row, column);
        return;
      }
      --target;
    }
  }
}

Player getRandomStartingPlayer() {
  static std::mt19937 engine{std::random_device{}()};
  std::uniform_int_distribution<int> distribution(0, 1);

  return distribution(engine) == 0 ? Player::XPlayer : Player::OPlayer;
}

static Player gameLoop(const PlayMode playMode, const unsigned int boardSize) {
  bool finished = false;
  Player victoryPlayer = Player::Tie;
  auto row = 0u, column = 0u;

  std::vector<char> data(boardSize * boardSize, EMPTY_PIECE);

  Player currentPlayer = getRandomStartingPlayer();

  std::cout << "Starting player is: " << playerToPiece(currentPlayer)
            << std::endl;

  do {

    drawBoard(data, boardSize);

    // Get input
    if (playMode == PlayMode::Machine && currentPlayer == Player::OPlayer) {
      machinePlay(data, boardSize, row, column);
    } else {
      getPosition(data, boardSize, row, column);
    }

    data[row * boardSize + column] = playerToPiece(currentPlayer);

    finished = checkVictory(data, boardSize, victoryPlayer);

    if (!finished) {
      currentPlayer = nextPlayer(currentPlayer);
      std::cout << "Turn of player " << playerToPiece(currentPlayer)
                << std::endl;
    }
  } while (!finished);

  // Draw
  drawBoard(data, boardSize);

  return victoryPlayer;
}

int main() {
  std::string confirmation;
  auto continueProgram = false;

  std::cout << "Welcome to Tic Tac Toe" << std::endl;
  std::cout << "This program let you play against Tic Tac Toe against the "
               "machine or another player."
            << std::endl;

  do {
    const auto playMode = getPlayMode();

    const auto boardSize = getBoardSize();

    const auto victoryPlayer = gameLoop(playMode, boardSize);

    if (Player::Tie == victoryPlayer) {
      std::cout << "The match is a tie!" << std::endl;
    } else {
      std::cout << "The player playing " << playerToPiece(victoryPlayer)
                << " won!" << std::endl;
    }

    continueProgram = askContinue();
  } while (continueProgram);

  return EXIT_SUCCESS;
}
