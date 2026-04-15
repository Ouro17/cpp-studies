#ifndef FUELLEVELCRITICAL_H
#define FUELLEVELCRITICAL_H

#include <stdexcept>

class FuelLevelCritical : public std::runtime_error{
    public:
    FuelLevelCritical();
    FuelLevelCritical(std::string err);
};


#endif