#include "Drone.hpp"

Drone::Drone(const std::string modelName, const double batteryLife) {
  this->modelName = modelName;
  this->batteryLife = batteryLife;
}

std::string Drone::getModelName() const { return this->modelName; }
double Drone::getBatteryLife() const { return this->batteryLife; }