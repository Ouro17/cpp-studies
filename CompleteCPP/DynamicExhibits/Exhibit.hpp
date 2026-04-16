#ifndef EXHIBIT_H
#define EXHIBIT_H

#include <string>

class Exhibit {
public:
  Exhibit(const std::string name, const int roomNumber, const double displaySize);

  std::string getName() const;
  int getRoomNumber() const;
  double getDisplaySize() const;

private:
  std::string name;
  int roomNumber;
  double displaySize;
};

#endif