//
// Created by lena on 3/16/18.
//

#include "AirportSim.h"

const vector<Airport *> &AirportSim::getAirports() const {
    return airports;
}

void AirportSim::setAirports(const vector<Airport *> &airports) {
    AirportSim::airports = airports;
}

const vector<Airplane *> &AirportSim::getAirplanes() const {
    return airplanes;
}

void AirportSim::setAirplanes(const vector<Airplane *> &airplanes) {
    AirportSim::airplanes = airplanes;
}

void AirportSim::simulate() {

}
