//
// Created by sam on 16.05.18.
//

#ifndef AIRPORTSIM_MEDIUMAIRPLANE_H
#define AIRPORTSIM_MEDIUMAIRPLANE_H


#include "airplane.h"

class MediumAirplane: public Airplane {
public:
    explicit MediumAirplane(Airplane* airplane): Airplane(airplane){}
    virtual void unboardPlane(std::ostream &output, const std::string& airport, int gate);
    virtual void checkPlane(std::ostream &output);
    virtual void boardPlane(std::ostream &output, const std::string& airport, int gate);
    virtual void pushBack(std::ostream &output);
    virtual void consumeFuel();
};


#endif //AIRPORTSIM_MEDIUMAIRPLANE_H
