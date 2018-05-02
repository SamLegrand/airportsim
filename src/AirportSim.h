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
    std::string airleaderoutput;
public:
    AirportSim();
    AirportSim(const std::string &airleaderoutput);
    bool properlyInitialized();

    const std::vector<Airport *> &getAirports();
    void setAirports(const std::vector<Airport *> &airports);

    const std::vector<Airplane *> &getAirplanes();
    void setAirplanes(const std::vector<Airplane *> &airplanes);

    void simulate(std::ostream &output);
    bool checkSimEnd();
};


#endif //AIRPORTSIM_AIRPORTSIM_H
