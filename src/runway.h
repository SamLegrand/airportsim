//
// Created by lena on 3/29/18.
//

#ifndef AIRPORTSIM_RUNWAY_H
#define AIRPORTSIM_RUNWAY_H

#include "airplane.h"
#include <string>

class Runway {
    std::string name;
    Airplane* airplane;
public:
    Runway();

    const std::string &getName() const;

    void setName(const std::string &name);

    Airplane *getAirplane() const;

    void setAirplane(Airplane *airplane);
};


#endif //AIRPORTSIM_RUNWAY_H
