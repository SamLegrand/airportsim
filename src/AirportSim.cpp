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
    Airport* airport = airports[0];
    while (!checkSimEnd()) {
        for (Airplane *airplane : airplanes) {
            if (airplane->getStatus() == "Travelling") {
                continue;
            }
            if (airplane->getStatus() == "Leaving Airport") {
                airplane->leaveAirport(airport->getName());
                continue;
            }
            if (airplane->getStatus() == "Ascending") {
                airplane->ascend();
                continue;
            }
            if (airplane->getStatus() == "Taxiing to Runway") {
                Runway *runway = airport->getAvailableRunway();
                if (runway == NULL) {
                    continue;
                }
                airplane->takeOff(airport->getName(), runway->getName());
                continue;
            }
            if (airplane->getStatus() == "Boarded Plane") {
                Runway *runway = airport->getAvailableRunway();
                if (runway == NULL) {
                    continue;
                }
                airplane->taxiToRunway(runway->getName());
                airport->removePlane(airplane);
                continue;
            }
            if (airplane->getStatus() == "Refueled Plane") {
                airplane->boardPlane(airport->getName(), airport->getAvailableGate());
                continue;
            }
            if (airplane->getStatus() == "Checked Plane") {
                airplane->refuelPlane();
                continue;
            }
            if (airplane->getStatus() == "Unboarded Plane") {
                airplane->checkPlane();
                continue;
            }
            if (airplane->getStatus() == "Standing at Gate") {
                airplane->unboardPlane(airport->getName(), airport->getAvailableGate());
                continue;
            }
            if (airplane->getStatus() == "Taxiing to Gate") {
                int gate = airport->getAvailableGate();
                if (gate == -1) {
                    continue;
                }
                airport->addPlane(airplane, gate);
                airplane->stand(gate);
                continue;
            }
            if (airplane->getStatus() == "Awaiting Taxi") {
                airplane->taxiToGate(airport->getAvailableGate());
                continue;
            }
            if (airplane->getStatus() == "Landed") {
                airplane->landed(airport->getName(), airport->getAvailableRunway()->getName());
                continue;
            }
            if (airplane->getStatus() == "Landing") {
                airplane->land(airport->getName(), airport->getAvailableRunway()->getName());
                continue;
            }
            if (airplane->getStatus() == "Descending") {
                airplane->descend();
                continue;
            }
            if (airplane->getStatus() == "Approaching") {
                airplane->approach(airport->getName());
                continue;
            }
        }
    }
}

bool AirportSim::checkSimEnd() {
    for(Airplane* airplane : airplanes) {
        if (airplane->getStatus() != "Travelling") {
            return false;
        }
    }
    return true;
}
