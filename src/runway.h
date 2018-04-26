//
// Created by lena on 3/29/18.
//

#ifndef AIRPORTSIM_RUNWAY_H
#define AIRPORTSIM_RUNWAY_H

#include "airplane.h"
#include <string>
#include <vector>

class Airplane;

class Runway {
    std::string name;
    std::string type;
    int length;
    Airplane* airplane;
    Airplane* airplaneCrossing;
    std::vector<std::string> taxipoints;
    std::vector<std::string> crossings;
public:
    Runway();

    const std::string &getName() const;

    void setName(const std::string &name);

    Airplane *getAirplane() const;

    void setAirplane(Airplane *airplane);

    const std::string &getType() const;

    void setType(const std::string &type);

    int getLength() const;

    void setLength(int length);

    void addTaxipoint(std::string taxipoint);

    void addCrossing(std::string crossing);

    const std::vector<std::string> &getTaxipoints() const;

    const std::vector<std::string> &getCrossings() const;

    Airplane *getAirplaneCrossing() const;

    void setAirplaneCrossing(Airplane *airplaneCrossing);
};


#endif //AIRPORTSIM_RUNWAY_H
