//
// Created by sam on 16.05.18.
//

#ifndef AIRPORTSIM_LARGEAIRPLANE_H
#define AIRPORTSIM_LARGEAIRPLANE_H


#include "airplane.h"

class LargeAirplane: public Airplane {
public:
    explicit LargeAirplane(Airplane* airplane): Airplane(airplane){}
    virtual void unboardPlane(std::ostream &output, const std::string& airport, int gate);
    virtual void checkPlane(std::ostream &output);
    virtual void boardPlane(std::ostream &output, const std::string& airport, int gate);
    virtual void pushBack(std::ostream &output);
};


#endif //AIRPORTSIM_LARGEAIRPLANE_H
