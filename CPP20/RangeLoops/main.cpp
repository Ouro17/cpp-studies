#include <cstdlib>
#include <list>
#include <mutex>
#include <print>

class Names {
  std::list<std::string> names{};

public:
  Names(std::list<std::string> names) : names(std::move(names)) {
    std::print("Constructing Names\n");
  }

  ~Names() { std::print("Destructing Names\n"); }

  std::list<std::string> &get() { return names; }
};

Names Create() { return {{"C#", "C++", "C"}}; }

int main() {
  std::list<int> data{1, 2, 3, 4};
  // int data[]{1,2,3,4};

  const auto &range = data;
  auto begining = std::begin(range);
  auto ending = std::end(range);

  for (; begining != ending; ++begining) {
    const auto element = *begining;
    std::print("{}\n", element);
  }

  std::print("Or\n");

  for (const auto &element : data) {
    std::print("{}\n", element);
  }

  std::print("Creating temporary object\n");

  for (auto names = Create(); auto &name : names.get()) {
    std::print("{}\n", name);
  }

  std::print("Example with mutex, lock will release at the end of the loop.\n");
  std::mutex mtx{};

  for (std::lock_guard lck{mtx}; auto x : {1, 2, 3}) {
    std::print("{}\n", x);
  }

  return EXIT_SUCCESS;
}