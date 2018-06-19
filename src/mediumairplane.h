//
// Created by sam on 16.05.18.
//

#ifndef AIRPORTSIM_MEDIUMAIRPLANE_H
#define AIRPORTSIM_MEDIUMAIRPLANE_H


#include "airplane.h"

class MediumAirplane: public Airplane {
public:
    MediumAirplane(): Airplane(){}
    explicit MediumAirplane(Airplane* airplane): Airplane(airplane){}
    virtual void unboardPlane(std::ostream &output, const std::string& airport, int gate);
    virtual void checkPlane(std::ostream &output);
    virtual void boardPlane(std::ostream &output, const std::string& airport, int gate);
    virtual void pushBack(std::ostream &output);
    virtual void consumeFuel();
    virtual void unboardAtRunway(std::ostream &output, const std::string &airport, const std::string &runway);
    virtual void checkAtRunway(std::ostream &output);
    virtual void refuelAtRunway(std::ostream &output);
    virtual void refuelPlane(std::ostream &output);
};


#endif //AIRPORTSIM_MEDIUMAIRPLANE_H
