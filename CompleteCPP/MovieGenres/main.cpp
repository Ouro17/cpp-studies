#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>

int main() {
  std::cout << "Welcome to the movie genre report" << std::endl;
  std::cout << "This program aggregates the movie genres in genres.txt file"
            << std::endl;
  std::cout << "and also some statistics" << std::endl;

  auto inputFile = std::ifstream("genres.txt");

  if (!inputFile) {
    std::cerr << "Error opening the file. Exiting program...";
    return EXIT_FAILURE;
  }

  std::map<std::string, uint> genres;
  auto totalVotes = 0u;

  std::string readGenre;
  while (inputFile >> readGenre) {

    if (readGenre.empty()) {
      continue;
    }

    genres[readGenre]++;
    totalVotes++;
  }

  inputFile.close();

  for (const auto &pair : genres) {
    std::cout << "Genre: " << pair.first << " has " << pair.second << " votes, percentage: "  << (100 * pair.second) / totalVotes << std::endl;
  }

  return EXIT_SUCCESS;
}