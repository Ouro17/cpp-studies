#include "FuelLevelCritical.hpp"

FuelLevelCritical::FuelLevelCritical()
    : std::runtime_error("Fuel level is critical! Must refuel immediately!") {}

FuelLevelCritical::FuelLevelCritical(std::string err)
    : std::runtime_error(err) {}