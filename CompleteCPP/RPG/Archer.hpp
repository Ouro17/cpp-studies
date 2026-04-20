#ifndef ARCHER_H
#define ARCHER_H
#include "Player.hpp"

class Archer : public Player {
public:
  Archer(std::string name, Race race) : Player(name, race, 100, 100) {};
  std::string_view attack() const override { return "Catch me if you can!"; }
};

#endif