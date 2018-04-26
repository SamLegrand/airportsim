//
// Created by lena on 3/16/18.
//

#include "AirportSim.h"

const std::vector<Airport *> &AirportSim::getAirports() const {
    return airports;
}

void AirportSim::setAirports(const std::vector<Airport *> &airports) {
    AirportSim::airports = airports;
}

const std::vector<Airplane *> &AirportSim::getAirplanes() const {
    return airplanes;
}

void AirportSim::setAirplanes(const std::vector<Airplane *> &airplanes) {
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
                if (runway != NULL) {
                    runway->setAirplane(NULL);
                }
                airplane->ascend(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Taking Off") {
                Runway *runway = airport->findPlaneInRunway(airplane);
                if (runway == NULL) {
                    continue;
                }
                airplane->takeOff(SimOutput, airport->getName(), runway->getName());
                continue;
            }
            if (airplane->getStatus() == "Taxiing to Runway") {
                if (airport->findPlaneInGate(airplane) != -1){
                    airport->removePlaneFromGate(airplane);
                    airplane->setEndpoint(airport->getAvailableRunway());
                    Runway* runway = airplane->getEndpoint();
                    if (runway == NULL) {
                        continue;
                    }
                    if (runway->getCrossings().size() > 0){
                        SimOutput << airplane->getCallsign() << " is taxiing to holding point " << runway->getCrossings().front() << " via " << runway->getTaxipoints().front() << std::endl;
                        airplane->setCrossing(airport->findRunway(runway->getCrossings().front()));
                    }
                    else{
                        SimOutput << airplane->getCallsign() << " is taxiing to runway " << runway->getName() << " via " << runway->getTaxipoints().back() << std::endl;
                        runway->setAirplaneCrossing(NULL);
                        airplane->taxiToRunway(SimOutput, runway->getName());
                        runway->setAirplane(airplane);
                    }
                }
                else if (airplane->getCrossing() == NULL){
                    Runway* runway = airplane->getEndpoint();
                    if (!runway->getCrossings().empty()){
                        Runway* runway2 = airport->findPlaneInCrossing(airplane);
                        for (unsigned int j = 0; j < runway->getCrossings().size(); ++j) {
                            if (airport->findRunway(runway->getCrossings()[j]) == runway2 && j - 1 >= 0){
                                SimOutput << airplane->getCallsign() << " is taxiing to holding point " << runway->getCrossings()[j - 1] << " via " << runway->getTaxipoints()[j] << std::endl;
                                runway->setAirplaneCrossing(NULL);
                                airplane->setCrossing(airport->findRunway(runway->getCrossings()[j - 1]));
                            }
                        }
                    }
                    if (airport->findPlaneInCrossing(airplane) != NULL){
                        SimOutput << airplane->getCallsign() << " is taxiing to runway " << runway->getName() << " via " << runway->getTaxipoints().back() << std::endl;
                        runway->setAirplaneCrossing(NULL);
                        airplane->taxiToRunway(SimOutput, runway->getName());
                        runway->setAirplane(airplane);
                    }
                }
                else{
                    Runway* runway = airplane->getCrossing();
                    if (runway->getAirplane() == NULL){   //If runway is not occupied
                        SimOutput << airplane->getCallsign() << " is crossing " << runway->getName() << std::endl;
                        airplane->setCrossing(NULL);
                        runway->setAirplaneCrossing(airplane);
                    }
                    else{
                        SimOutput << airplane->getCallsign() << " is holding short at " << runway->getName() << std::endl;
                    }
                }
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
                if (airport->findPlaneInRunway(airplane) != NULL) { //Remove plane from the runway that it landed on
                    Runway *runway = airport->findPlaneInRunway(airplane);
                    runway->setAirplane(NULL);
                    runway->setAirplaneCrossing(airplane);
                }
                if (airplane->getCrossing() == NULL){
                    Runway *runway = airport->findPlaneInCrossing(airplane);
                    if (!runway->getCrossings().empty()){
                        SimOutput << airplane->getCallsign() << " is taxiing to holding point " << runway->getCrossings().back() << " via " << runway->getTaxipoints().back() << std::endl;
                        runway->setAirplaneCrossing(NULL);
                        airplane->setCrossing(airport->findRunway(runway->getCrossings().back()));
                    }
                    else{
                        int gate = airport->getAvailableGate();
                        if (gate == -1) {
                            continue;
                        }
                        airport->addPlaneToGate(airplane, gate);
                        airplane->taxiToGate(SimOutput, gate);
                    }
                }
                else{
                    Runway* runway = airplane->getCrossing();
                    if (runway->getAirplane() == NULL){   //If runway is not occupied
                        SimOutput << airplane->getCallsign() << " is crossing " << runway->getName() << std::endl;
                        runway->setAirplaneCrossing(airplane);
                        airplane->setCrossing(NULL);
                    }
                    else{
                        SimOutput << airplane->getCallsign() << " is holding short at " << runway->getName() << std::endl;
                    }
                }
                continue;
            }
            if (airplane->getStatus() == "Landed") {
                Runway* runway = airport->findPlaneInRunway(airplane);
                airplane->landed(SimOutput, airport->getName(), runway->getName());
                continue;
            }
            if (airplane->getStatus() == "Landing") {
                Runway* runway = airport->findPlaneInRunway(airplane);
                airplane->land(SimOutput, airport->getName(), runway->getName());
                continue;
            }
            if (airplane->getStatus() == "Final Approach") {
                Runway* runway = airport->findPlaneInRunway(airplane);
                if (runway == NULL) {
                    runway = airport->getAvailableRunway();
                    if (runway == NULL) {
                        airplane->finalapproach(SimOutput, airport->getName(), "");
                        continue;
                    } else {
                        runway->setAirplane(airplane);
                    }
                }
                airplane->finalapproach(SimOutput, airport->getName(), runway->getName());
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
