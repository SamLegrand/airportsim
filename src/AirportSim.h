//
// Created by lena on 3/16/18.
//

#ifndef AIRPORTSIM_AIRPORTSIM_H
#define AIRPORTSIM_AIRPORTSIM_H


#include "airport.h"

class AirportSim {
    AirportSim* initCheck;
    std::vector<Airport*> airports;
    std::vector<Airplane*> airplanes;
public:
    AirportSim();

    bool properlyInitialized();

    const std::vector<Airport *> &getAirports() const;

    void setAirports(const std::vector<Airport *> &airports);

    const std::vector<Airplane *> &getAirplanes() const;

    void setAirplanes(const std::vector<Airplane *> &airplanes);

    void simulate(std::ostream &output);

    bool checkSimEnd();

    void taxiToGate(Airport* &airport, Airplane* &airplane, std::ostream &SimOutput);
};


#endif //AIRPORTSIM_AIRPORTSIM_H
