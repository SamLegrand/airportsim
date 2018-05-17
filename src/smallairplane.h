//
// Created by sam on 16.05.18.
//

#ifndef AIRPORTSIM_SMALLAIRPLANE_H
#define AIRPORTSIM_SMALLAIRPLANE_H


#include "airplane.h"

class SmallAirplane: public Airplane {
public:
    explicit SmallAirplane(Airplane* airplane): Airplane(airplane){}
    virtual void unboardPlane(std::ostream &output, const std::string& airport, int gate);
    virtual void checkPlane(std::ostream &output);
    virtual void boardPlane(std::ostream &output, const std::string& airport, int gate);
    virtual void pushBack(std::ostream &output);
};


#endif //AIRPORTSIM_SMALLAIRPLANE_H
