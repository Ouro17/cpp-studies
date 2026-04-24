#include "Crop.hpp"
#include <cstdlib>
#include <memory>
#include <print>
#include <vector>

template <std::ranges::input_range TRange>
static void printRange(const TRange &data) {
  for (const auto &element : data) {
    std::print("{}\n", *element);
  }
}

int main() {

  std::vector<std::unique_ptr<Crop>> data;

  data.reserve(3);

  data.emplace_back(std::make_unique<Crop>(23u, 7, 1));
  data.emplace_back(std::make_unique<Crop>(30u, 3, 8));
  data.emplace_back(std::make_unique<Crop>(15u, 8, 5));

  printRange(data);

  std::print("Is first greater than second? {}\n", data[0] > data[1]);
  std::print("Is first less than second? {}\n", data[0] < data[1]);
  std::print("Is first different than second? {}\n", data[0] != data[1]);

  std::print("Is second greater than third? {}\n", data[1] > data[2]);
  std::print("Is second less than third? {}\n", data[1] < data[2]);
  std::print("Is second equal than third? {}\n", data[1] == data[2]);

  auto f0001 = *data[0] + *data[1];
  auto f0102 = *data[1] + *data[2];

  std::print("Hybrid first and second {}\n", f0001);
  std::print("Hybrid second and third {}\n", f0102);

  return EXIT_SUCCESS;
}