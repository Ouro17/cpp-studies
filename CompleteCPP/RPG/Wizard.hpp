#ifndef WIZARD_H
#define WIZARD_H
#include "Player.hpp"

class Wizard : public Player {
public:
  Wizard(std::string name, Race race) : Player(name, race, 50, 200) {};
  std::string_view attack() const override { return "Magic fireball!"; }
};

#endif