//
// Created by lena on 3/29/18.
//

#ifndef AIRPORTSIM_RUNWAY_H
#define AIRPORTSIM_RUNWAY_H

#include "airplane.h"
#include <string>
#include <vector>

class Runway {
    std::string name;
    std::string type;
    int length;
    Airplane* airplane;
    vector<string> taxipoints;
    vector<string> crossings;
public:
    Runway();

    const std::string &getName() const;

    void setName(const std::string &name);

    Airplane *getAirplane() const;

    void setAirplane(Airplane *airplane);

    const string &getType() const;

    void setType(const string &type);

    int getLength() const;

    void setLength(int length);

    void addTaxipoint(string taxipoint);

    void addCrossing(string crossing);

    const vector<string> &getTaxipoints() const;

    const vector<string> &getCrossings() const;
};


#endif //AIRPORTSIM_RUNWAY_H
