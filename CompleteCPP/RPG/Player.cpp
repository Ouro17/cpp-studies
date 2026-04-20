#include "Player.hpp"

Player::Player(std::string name, Race race, int hitPoints, int magicPoints) {
  this->name = name;
  this->race = race;
  this->hitPoints = hitPoints;
  this->magicPoints = magicPoints;
}

std::string Player::getName() const { return name; }

Race Player::getRace() const { return race; }

int Player::getHitPoints() const { return hitPoints; }

int Player::getMagicPoints() const { return magicPoints; }

void Player::setName(std::string newValue) { name = newValue; }

void Player::setRace(Race newValue) { race = newValue; }

void Player::setHitPoints(int newValue) { hitPoints = newValue; }

void Player::setMagicPoints(int newValue) { magicPoints = newValue; }

std::string_view Player::attack() const { return "Basic attack"; }
