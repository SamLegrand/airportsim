//
// Created by sam on 01.03.18.
//

#include "airport.h"

void Airport::setName(const std::string &name) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    Airport::name = name;
}

void Airport::setIata(const std::string &iata) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    Airport::iata = iata;
}

void Airport::setCallsign(const std::string &callsign) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    Airport::callsign = callsign;
}

void Airport::setRunways(const std::vector<Runway *> &runways) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    Airport::runways = runways;
}

void Airport::setGates(const unsigned int &gate) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    gates.reserve(gate);
    for (unsigned int i = 0; i < gate; i++) {
        gates.push_back(NULL);
    }
}

void Airport::setPassengers(const int &passengers) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    Airport::passengers = passengers;
}

const std::string &Airport::getName() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return name;
}

const std::string &Airport::getIata() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return iata;
}

const std::string &Airport::getCallsign() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return callsign;
}

const std::vector<Runway *> &Airport::getRunways() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return runways;
}

const std::vector<Airplane*> &Airport::getGatesVector() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return gates;
}

const int Airport::getGates() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return (int)gates.size();
}

const int &Airport::getPassengers() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return passengers;
}

void Airport::printInfo(std::ofstream &output) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    output << "Airport: " << name << " (" << iata << ")" << std::endl;
    output << " -> gates: " << gates.size() << std::endl;
    output << " -> runways: " << runways.size() << std::endl;
}

int Airport::getAvailableGate() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
    for (unsigned int i = 0; i < gates.size(); i++) {
        if(gates[i] == NULL){
            return i + 1;
        }
    }
    return -1;
}

void Airport::addPlaneToGate(Airplane *airplane, int gate) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(gate > 0 && gate <= this->getGates(), "Gate should be a valid value.");
    gates[gate - 1] = airplane;
    ENSURE(this->findPlaneInGate(airplane) == gate, "Plane wasn't added to correct gate.");
}

int Airport::findPlaneInGate(Airplane *airplane) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
    for (unsigned int i = 0; i < gates.size(); ++i) {
        if(gates[i] == airplane){
            return i + 1;
        }
    }
    return -1;
}

void Airport::removePlaneFromGate(Airplane *airplane) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
    for (unsigned int i = 0; i < gates.size(); i++) {
        if(gates[i] == airplane){
            gates[i] = NULL;
            ENSURE(this->findPlaneInGate(airplane) == -1, "Plane wasn't correctly removed from gate.");
        }
    }
}

void Airport::addRunway(Runway *_runway) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(_runway->getAirplane() == NULL, "Runway isn't properly initialised.");
    runways.push_back(_runway);
}

void Airport::addPlaneToRunway(Airplane *airplane, int runway) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(runway > 0 && (unsigned)runway < this->getRunways().size(), "Runway should be a valid value.");
    runways[runway]->setAirplane(airplane);
}

void Airport::removePlaneFromRunway(Airplane *airplane) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); i++) {
        if(runways[i]->getAirplane() == airplane){
            runways[i]->setAirplane(NULL);
            ENSURE(this->findPlaneInRunway(airplane) == NULL, "Plane wasn't correctly removed from runway.");
        }
    }
}

Runway *Airport::getAvailableRunway() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); i++) {
        if(runways[i]->getAirplane() == NULL){
            return runways[i];
        }
    }
    return NULL;
}

Runway *Airport::getRunwayByAirplane(Airplane* airplane) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); i++) {
        if(runways[i]->getAirplane() == NULL){
            if (airplane->getSize() == "small" && airplane->getEngine() == "propeller"){
                if (runways[i]->getLength() >= 500){
                    return runways[i];
                }
            }
            else{
                if (runways[i]->getType() == "grass"){
                    continue;
                }
                if (airplane->getSize() == "small"){
                    if (runways[i]->getLength() >= 1000){
                        return runways[i];
                    }
                }
                if (airplane->getSize() == "medium"){
                    if (airplane->getEngine() == "propeller"){
                        if (runways[i]->getLength() >= 1000){
                            return runways[i];
                        }
                    }
                    if (airplane->getEngine() == "jet"){
                        if (runways[i]->getLength() >= 2000){
                            return runways[i];
                        }
                    }
                }
                if (airplane->getSize() == "large"){
                    if (airplane->getEngine() == "propeller"){
                        if (runways[i]->getLength() >= 1500){
                            return runways[i];
                        }
                    }
                    if (airplane->getEngine() == "jet"){
                        if (runways[i]->getLength() >= 3000){
                            return runways[i];
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

Runway *Airport::findPlaneInRunway(Airplane* airplane) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->getAirplane() == airplane){
            return runways[i];
        }
    }
    return NULL;
}

Runway *Airport::findRunwayByRunwayName(std::string runwayName) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if (runways[i]->getName() == runwayName){
            return runways[i];
        }
    }
    return NULL;
}

Runway *Airport::findPlaneInCrossing(Airplane *airplane) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->getAirplaneCrossing() == airplane){
            return runways[i];
        }
    }
    return NULL;
}

Airplane *Airport::getH3000() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return h3000;
}

void Airport::setH3000(Airplane *h3000) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    Airport::h3000 = h3000;
}

Airplane *Airport::getH5000() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return h5000;
}

void Airport::setH5000(Airplane *h5000) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    Airport::h5000 = h5000;
}

Airport::Airport() {
    h3000 = NULL;
    h5000 = NULL;
    initCheck = this;
    ENSURE(this->properlyInitialized(), "Airport wasn't properly initialized.");
}

bool Airport::properlyInitialized(){
    return initCheck == this;
}

const std::vector<std::string> &Airport::getTaxipoints() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    return taxipoints;
}

void Airport::setTaxipoints(const std::vector<std::string> &taxipoints) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    Airport::taxipoints = taxipoints;
}

Runway *Airport::findRunwayByTaxiName(std::string taxipoint) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if (runways[i]->getTaxipoint() == taxipoint){
            return runways[i];
        }
    }
    return NULL;
}

Runway *Airport::findNextRunwayToGate(Runway *runway) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size()-1; ++i) {
        if (runways[i] == runway){
            return runways[i+1];
        }
    }
    return NULL;
}

Runway *Airport::findNextRunwayToRunway(Runway *runway) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 1; i < runways.size(); ++i) {
        if (runways[i] == runway){
            return runways[i-1];
        }
    }
    return NULL;
}

Runway *Airport::findRunwayByTaxipointToGate(Airplane *airplane) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if (runways[i]->getTaxipointToGate() == airplane){
            return runways[i];
        }
    }
    return NULL;
}

Runway *Airport::findRunwayByTaxipointToRunway(Airplane *airplane) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if (runways[i]->getTaxipointToRunway() == airplane){
            return runways[i];
        }
    }
    return NULL;
}

void Airport::sortRunways() {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    std::vector<Runway*> sortedRunways;
    for (int i = taxipoints.size()-1; i>-1; i--) {
        sortedRunways.push_back(findRunwayByTaxiName(taxipoints[i]));
    }
    runways = sortedRunways;
}

Runway *Airport::findNearestAvailableRunway(Airplane* airplane) {
    REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (int i = runways.size()-1; i > -1; i--) {
        if(runways[i]->getAirplane() == NULL){
            if (airplane->getSize() == "small" && airplane->getEngine() == "propeller"){
                if (runways[i]->getLength() >= 500){
                    return runways[i];
                }
            }
            else{
                if (runways[i]->getType() == "grass"){
                    continue;
                }
                if (airplane->getSize() == "small"){
                    if (runways[i]->getLength() >= 1000){
                        return runways[i];
                    }
                }
                if (airplane->getSize() == "medium"){
                    if (airplane->getEngine() == "propeller"){
                        if (runways[i]->getLength() >= 1000){
                            return runways[i];
                        }
                    }
                    if (airplane->getEngine() == "jet"){
                        if (runways[i]->getLength() >= 2000){
                            return runways[i];
                        }
                    }
                }
                if (airplane->getSize() == "large"){
                    if (airplane->getEngine() == "propeller"){
                        if (runways[i]->getLength() >= 1500){
                            return runways[i];
                        }
                    }
                    if (airplane->getEngine() == "jet"){
                        if (runways[i]->getLength() >= 3000){
                            return runways[i];
                        }
                    }
                }
            }
        }
    }
    return NULL;
}
