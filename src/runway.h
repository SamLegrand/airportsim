//
// Created by lena on 3/29/18.
//

#ifndef AIRPORTSIM_RUNWAY_H
#define AIRPORTSIM_RUNWAY_H

#include "airplane.h"
#include "Taxipoint.h"
#include <string>
#include <vector>

class Airplane;
class Taxipoint;

class Runway {
    Runway* initCheck;
    std::string name;
    std::string type;
    int length;
    Airplane* airplane;
    Airplane* taxipointToRunway;
    Airplane* taxipointToGate;
    Airplane* crossingToRunway;
    Airplane* crossingToGate;
    std::string taxipoint;
public:
    Runway();

    Airplane *getTaxipointToRunway() const;

    void setTaxipointToRunway(Airplane *taxipointToRunway);

    Airplane *getTaxipointToGate() const;

    void setTaxipointToGate(Airplane *taxipointToGate);

    Airplane *getCrossingToRunway() const;

    void setCrossingToRunway(Airplane *crossingToRunway);

    Airplane *getCrossingToGate() const;

    void setCrossingToGate(Airplane *crossingToGate);

    const std::string &getTaxipoint() const;

    void setTaxipoint(const std::string &taxipoint);

    bool properlyInitialized();

    const std::string &getName() const;

    void setName(const std::string &name);

    Airplane *getAirplane() const;

    void setAirplane(Airplane *airplane);

    const std::string &getType() const;

    void setType(const std::string &type);

    int getLength() const;

    void setLength(int length);

    bool ableToCross();
};


#endif //AIRPORTSIM_RUNWAY_H
