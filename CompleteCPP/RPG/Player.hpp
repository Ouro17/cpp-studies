#ifndef PLAYER_H
#define PLAYER_H
#include "Race.hpp"
#include <string>
#include <string_view>

class Player {

public:
  Player(std::string name, Race race, int hitPoints, int magicPoints);
  virtual ~Player() = default;

  std::string getName() const;
  Race getRace() const;
  int getHitPoints() const;
  int getMagicPoints() const;

  void setName(std::string newValue);
  void setRace(Race newValue);
  void setHitPoints(int newValue);
  void setMagicPoints(int newValue);

  virtual std::string_view attack() const;

private:
  std::string name;
  Race race;
  int hitPoints;
  int magicPoints;
};

#endif