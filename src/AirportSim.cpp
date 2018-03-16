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
                airplane->ascend(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Taking Off") {
                Runway *runway = airport->getAvailableRunway();
                if (runway == NULL) {
                    break;
                }
                airplane->takeOff(SimOutput, airport->getName(), runway->getName());
                continue;
            }
            if (airplane->getStatus() == "Taxiing to Runway") {
                Runway *runway = airport->getAvailableRunway();
                if (runway == NULL) {
                    break;
                }
                airplane->taxiToRunway(SimOutput, runway->getName());
                airport->removePlane(airplane);
                continue;
            }
            if(airplane->getStatus() == "Standing at Gate"){
                airplane->stand(SimOutput, airport->findPlane(airplane));
            }
            if (airplane->getStatus() == "Boarded Plane") {
                airplane->boardPlane(SimOutput, airport->getName(), airport->findPlane(airplane));
                continue;
            }
            if (airplane->getStatus() == "Refueled Plane") {
                airplane->refuelPlane(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Checked Plane") {
                airplane->checkPlane(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Unboarded Plane") {
                airplane->unboardPlane(SimOutput, airport->getName(), airport->findPlane(airplane));
                continue;
            }
            if (airplane->getStatus() == "Taxiing to Gate") {
                int gate = airport->getAvailableGate();
                if (gate == -1) {
                    break;
                }
                airport->addPlane(airplane, gate);
                airplane->taxiToGate(SimOutput, gate);
                continue;
            }
            if (airplane->getStatus() == "Landed") {
                airplane->landed(SimOutput, airport->getName(), airport->getAvailableRunway()->getName());
                continue;
            }
            if (airplane->getStatus() == "Landing") {
                airplane->land(SimOutput, airport->getName(), airport->getAvailableRunway()->getName());
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
