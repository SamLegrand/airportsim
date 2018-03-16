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

void AirportSim::simulate(std::ostream& SimOutput) {
    Airport* airport = airports[0];
    while (!checkSimEnd()) {
        for (unsigned int i = 0; i<airplanes.size(); ++i) {
            Airplane* airplane = airplanes[i];
            if (airplane->getStatus() == "Travelling") {
                continue;
            }
            if (airplane->getStatus() == "Leaving Airport") {
                airplane->leaveAirport(SimOutput, airport->getName());
                continue;
            }
            if (airplane->getStatus() == "Ascending") {
                Runway* runway = airport->findPlaneInRunway(airplane);
                airplane->ascend(SimOutput);
                runway->airplane = NULL;
                continue;
            }
            if (airplane->getStatus() == "Taking Off") {
                Runway *runway = airport->findPlaneInRunway(airplane);
                if (runway == NULL) {
                    continue;
                }
                airplane->takeOff(SimOutput, airport->getName(), runway->name);
                continue;
            }
            if (airplane->getStatus() == "Taxiing to Runway") {
                Runway *runway = airport->getAvailableRunway();
                if (runway == NULL) {
                    continue;
                }
                airplane->taxiToRunway(SimOutput, runway->name);
                airport->removePlaneFromGate(airplane);
                runway->airplane = airplane;
                continue;
            }
            if(airplane->getStatus() == "Standing at Gate"){
                airplane->stand(SimOutput, airport->findPlaneInGate(airplane));
            }
            if (airplane->getStatus() == "Boarding Plane") {
                airplane->boardPlane(SimOutput, airport->getName(), airport->findPlaneInGate(airplane));
                continue;
            }
            if (airplane->getStatus() == "Refueling Plane") {
                airplane->refuelPlane(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Checking Plane") {
                airplane->checkPlane(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Unboarding Plane") {
                airplane->unboardPlane(SimOutput, airport->getName(), airport->findPlaneInGate(airplane));
                continue;
            }
            if (airplane->getStatus() == "Taxiing to Gate") {
                Runway* runway = airport->findPlaneInRunway(airplane);
                int gate = airport->getAvailableGate();
                if (gate == -1) {
                    continue;
                }
                airport->addPlaneToGate(airplane, gate);
                airplane->taxiToGate(SimOutput, gate);
                runway->airplane = NULL;
                continue;
            }
            if (airplane->getStatus() == "Landed") {
                Runway* runway = airport->findPlaneInRunway(airplane);
                airplane->landed(SimOutput, airport->getName(), runway->name);
                continue;
            }
            if (airplane->getStatus() == "Landing") {
                Runway* runway = airport->getAvailableRunway();
                if (runway == NULL) {
                    continue;
                }
                airplane->land(SimOutput, airport->getName(), runway->name);
                runway->airplane = airplane;
                continue;
            }
            if (airplane->getStatus() == "Descending") {
                airplane->descend(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Approaching") {
                airplane->approach(SimOutput, airport->getName());
                continue;
            }
        }
    }
}

bool AirportSim::checkSimEnd() {
    for (unsigned int i = 0; i<airplanes.size(); ++i) {
        Airplane* airplane = airplanes[i];
        if (airplane->getStatus() != "Travelling") {
            return false;
        }
    }
    return true;
}
