#include <cstdlib>
#include <format>
#include <print>
#include <ranges>
#include <vector>

class Test {
public:
  Test(int number) : number(number) {}

  int getNumber() const { return number; }

private:
  int number;
};

template <> struct std::formatter<Test> : std::formatter<int> {
  auto format(const Test &value, std::format_context &context) const {
    return std::formatter<int>::format(value.getNumber(), context);
  }
};

template <std::ranges::input_range TRange>
static void printRange(const TRange &data) {
  for (const auto &element : data) {
    std::print("{}\n", element);
  }
}

int main() {
  std::vector<Test> data;
  data.reserve(7);
  data.emplace_back(1);
  data.emplace_back(2);
  data.emplace_back(3);
  data.emplace_back(2);
  data.emplace_back(3);
  data.emplace_back(1);
  data.emplace_back(2);

  std::print("-----Before removing-----\n");

  printRange(data);

  std::erase_if(data,
                [](const Test &element) { return element.getNumber() == 2; });

  std::print("-----After removing-----\n");

  printRange(data);

  return EXIT_SUCCESS;
}