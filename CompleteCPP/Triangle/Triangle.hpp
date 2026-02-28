#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
public:
  Triangle();
  Triangle(double sideA, double sideB, double sideC);
  double getSideA() const;
  double getSideB() const;
  double getSideC() const;
  void setSideA(double newValue);
  void setSideB(double newValue);
  void setSideC(double newValue);

  bool isValid() const;
  double perimeter() const;
  double area() const;
  void print() const;

private:
  double sideA, sideB, sideC;
};

#endif