#include <cstdlib>
#include <print>
#include <vector>

class Test {
public:
  // Create constructor
  Test(int number) : number(number) { std::print("Created {}\n", number); }

  // Copy constructor
  Test(const Test &other) {
    number = other.number;
    std::print("Copied {}\n", number);
  }

  // Move constructor
  Test(Test &&other) noexcept : number(other.number) {
    std::print("Moved {}\n", number);
  }

private:
  int number;
};

int main() {
  std::vector<Test> data;
  data.reserve(3); // For testing move and copy, comment this line

  Test t1(1);

  std::print("-----Pushing back-----\n");
  data.push_back(t1);

  //data.push_back(1); // Another way, this will create and move

  std::print("-----Emplacing back-----\n");
  data.emplace_back(2);

  std::print("-----Emplacing back another one-----\n");
  data.emplace_back(3);

  return EXIT_SUCCESS;
}