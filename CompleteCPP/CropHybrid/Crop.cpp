#include "Crop.hpp"
#include <random>

static int getRandomInt(int minValue, int maxValue) {
  static std::random_device randomDevice;
  static std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<int> distribution(minValue, maxValue);

  return distribution(generator);
}

static int getAverageWithoutNegatives(int first, int second, int random) {
  auto value = (first + second) / 2 + random;
  if (value < 0) {
    value = 0;
  }

  return value;
}

Crop::Crop(int height, int yield, int droughtResistance) {
  this->height = height;
  this->yield = yield;
  this->droughtResistance = droughtResistance;
}

int Crop::getHeight() const { return height; }

int Crop::getYield() const { return yield; }

int Crop::getDroughtResistance() const { return droughtResistance; }

int Crop::getScore() const { return (height * 2) + (yield * 3)  + (droughtResistance * 4); }

Crop Crop::operator+(const Crop &other) const {
  return Crop(
      getAverageWithoutNegatives(this->height, other.height,
                                 getRandomInt(-2, 2)),
      getAverageWithoutNegatives(this->yield, other.yield, getRandomInt(-2, 2)),
      getAverageWithoutNegatives(this->droughtResistance,
                                 other.droughtResistance, getRandomInt(-2, 2)));
}

bool Crop::operator!=(const Crop &other) {
  return this->getScore() != other.getScore();
}

bool Crop::operator==(const Crop &other) {
  return this->getScore() == other.getScore();
}

bool Crop::operator<(const Crop &other) {
  return this->getScore() < other.getScore();
}

bool Crop::operator>(const Crop &other) {
  return this->getScore() > other.getScore();
}

bool Crop::operator>=(const Crop &other) {
  return this->getScore() >= other.getScore();
}

bool Crop::operator<=(const Crop &other) {
  return this->getScore() <= other.getScore();
}
