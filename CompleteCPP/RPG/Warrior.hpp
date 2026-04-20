#ifndef WARRIOR_H
#define WARRIOR_H
#include "Player.hpp"

class Warrior : public Player {
public:
  Warrior(std::string name, Race race) : Player(name, race, 200, 50) {};
  std::string_view attack() const override { return "By force we will win!"; }
};

#endif