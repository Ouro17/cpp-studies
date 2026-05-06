#include <cstdlib>
#include <print>
#include <string>

struct A {
  int a;
  int b;
};

struct B : A {
  int x;
  int y;
};

A FooA(A a) { return {a.a + 1, a.b - 1}; }

B FooB(B b) { return {b.a + 1, b.b - 1, b.x - 2, b.y + 2}; }

void printA(A a) { std::print("A Print: {},{}\n", a.a, a.b); }

void printB(B b) { std::print("B Print: {},{},{},{}\n", b.a, b.b, b.x, b.y); }

union Data {
  int x;
  char y;
  double z;
};

struct Department {
  std::string name;
  std::string manager;
};

struct Employee {
  int id;
  std::string name;
  Department dept{.name = "undefined"};
};

int main() {

  // Only works with aggregate types
  B b{1, 2}; // Dangerous, compiler dependent

  auto ta = FooA({5, 6});
  printA(ta);

  auto tb = FooB(b);
  printB(b);
  printA(b);
  printB(tb);

  A aTest{.a = 1};

  printA(aTest);

  Data d1{};
  Data d2{.x = 10};
  Data d3{.y = 'a'};

  // Unions can only have one designated parameter
  // Data d4{.x = 10, .y = 'a'};

  // CPP is more strict than C for designators

  Employee e1{};
  Employee e2{.name = "Test employee"};
  // It's better to designate the department name directly as in e3
  Employee e4{.id = 4, .name = "Test employee 4", .dept = "Department B"};
  std::print("{}\n", e4.dept.name);

  Employee e3{.id = 3, .name = "Test employee 3", .dept = {"Department A"}};

  // No mix, not change order of DI
  // Employee e5{.name = "Fail employee", 5};

  // Will override id
  Employee e6{.id = 10, .id = 20};

  std::print("{}\n", e6.id);

  return EXIT_SUCCESS;
}