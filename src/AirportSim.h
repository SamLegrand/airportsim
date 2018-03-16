//
// Created by lena on 3/16/18.
//

#ifndef AIRPORTSIM_AIRPORTSIM_H
#define AIRPORTSIM_AIRPORTSIM_H


#include "airport.h"

class AirportSim {
    vector<Airport*> airports;
    vector<Airplane*> airplanes;
public:
    const vector<Airport *> &getAirports() const;

    void setAirports(const vector<Airport *> &airports);

    const vector<Airplane *> &getAirplanes() const;

    void setAirplanes(const vector<Airplane *> &airplanes);

    void simulate();
};


#endif //AIRPORTSIM_AIRPORTSIM_H
