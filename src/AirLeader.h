//
// Created by vyolex on 4/27/18.
//

#ifndef AIRPORTSIM_AIRLEADER_H
#define AIRPORTSIM_AIRLEADER_H

#include "airport.h"
#include <sstream>

class AirLeader {
    std::ofstream output;
public:
    AirLeader();

    void printMessage(int time, std::string source, std::string message);
};


#endif //AIRPORTSIM_AIRLEADER_H
