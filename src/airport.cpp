//
// Created by sam on 01.03.18.
//

#include "airport.h"

void Airport::setName(const std::string &name) {
    Airport::name = name;
}

void Airport::setIata(const std::string &iata) {
    Airport::iata = iata;
}

void Airport::setCallsign(const std::string &callsign) {
    Airport::callsign = callsign;
}

void Airport::setRunways(const std::vector<Runway *> &runways) {
    Airport::runways = runways;
}

void Airport::setGates(const unsigned int &gate) {
    gates.reserve(gate);
    for (unsigned int i = 0; i < gate; i++) {
        gates.push_back(NULL);
    }
}

void Airport::setPassengers(const int &passengers) {
    Airport::passengers = passengers;
}

const std::string &Airport::getName() const {
    return name;
}

const std::string &Airport::getIata() const {
    return iata;
}

const std::string &Airport::getCallsign() const {
    return callsign;
}

const std::vector<Runway *> &Airport::getRunways() const {
    return runways;
}

const std::vector<Airplane*> &Airport::getGatesVector() const {
    return gates;
}

const int Airport::getGates() const {
    return (int)gates.size();
}

const int &Airport::getPassengers() const {
    return passengers;
}

void Airport::printInfo(std::ofstream &output) const {
    output << "Airport: " << name << " (" << iata << ")" << std::endl;
    output << " -> gates: " << gates.size() << std::endl;
    output << " -> runways: " << runways.size() << std::endl;
}

int Airport::getAvailableGate() {
    REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
    for (unsigned int i = 0; i < gates.size(); i++) {
        if(gates[i] == NULL){
            return i + 1;
        }
    }
    return -1;
}

void Airport::addPlaneToGate(Airplane *airplane, int gate) {
    REQUIRE(gate > 0 && gate <= this->getGates(), "Gate should be a valid value.");
    gates[gate - 1] = airplane;
    ENSURE(this->findPlaneInGate(airplane) == gate, "Plane wasn't added to correct gate.");
}

int Airport::findPlaneInGate(Airplane *airplane) {
    REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
    for (unsigned int i = 0; i < gates.size(); ++i) {
        if(gates[i] == airplane){
            return i + 1;
        }
    }
    return -1;
}

void Airport::removePlaneFromGate(Airplane *airplane) {
    REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
    for (unsigned int i = 0; i < gates.size(); i++) {
        if(gates[i] == airplane){
            gates[i] = NULL;
            ENSURE(this->findPlaneInGate(airplane) == -1, "Plane wasn't correctly removed from gate.");
        }
    }
}

void Airport::addRunway(Runway *_runway) {
    REQUIRE(_runway->getAirplane() == NULL, "Runway isn't properly initialised.");
    runways.push_back(_runway);
}

void Airport::addPlaneToRunway(Airplane *airplane, int runway) {
    REQUIRE(runway > 0 && (unsigned)runway < this->getRunways().size(), "Runway should be a valid value.");
    runways[runway]->setAirplane(airplane);
}

void Airport::removePlaneFromRunway(Airplane *airplane) {
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); i++) {
        if(runways[i]->getAirplane() == airplane){
            runways[i]->setAirplane(NULL);
            ENSURE(this->findPlaneInRunway(airplane) == NULL, "Plane wasn't correctly removed from runway.");
        }
    }
}

Runway *Airport::getAvailableRunway() {
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); i++) {
        if(runways[i]->getAirplane() == NULL){
            return runways[i];
        }
    }
    return NULL;
}

Runway *Airport::findPlaneInRunway(Airplane* airplane) {
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->getAirplane() == airplane){
            return runways[i];
        }
    }
    return NULL;
}

Runway *Airport::findRunway(std::string runwayName) {
    for (unsigned int i = 0; i < getRunways().size(); ++i) {
        if (getRunways()[i]->getName() == runwayName){
            return getRunways()[i];
        }
    }
    return NULL;
}

Runway *Airport::findPlaneInCrossing(Airplane *airplane) {
    REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->getAirplaneCrossing() == airplane){
            return runways[i];
        }
    }
    return NULL;
}

Runway *Airport::getFarthestRunway() {
    Runway* farthestRunway = runways[0];
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if (runways[i]->getCrossings().size() > farthestRunway->getCrossings().size()){
            farthestRunway = runways[i];
        }
    }
    return farthestRunway;
}

Airplane *Airport::getH3000() const {
    return h3000;
}

void Airport::setH3000(Airplane *h3000) {
    Airport::h3000 = h3000;
}

Airplane *Airport::getH5000() const {
    return h5000;
}

void Airport::setH5000(Airplane *h5000) {
    Airport::h5000 = h5000;
}

Airport::Airport() {
    h3000 = NULL;
    h5000 = NULL;
}

void Airport::setPlaneToGate(const Taxipoint *taxipoint, Airplane* &airplane) {
    for (unsigned int i = 0; i < getFarthestRunway()->getTaxipoints().size(); ++i) {
        if (getFarthestRunway()->getTaxipoints()[i]->getName() == taxipoint->getName()){
            getFarthestRunway()->getTaxipoints()[i]->setPlaneToGate(airplane);
        }
    }
}

void Airport::setPlaneToRunway(const Taxipoint *taxipoint, Airplane* &airplane) {
    for (unsigned int i = 0; i < getFarthestRunway()->getTaxipoints().size(); ++i) {
        if (getFarthestRunway()->getTaxipoints()[i]->getName() == taxipoint->getName()){
            getFarthestRunway()->getTaxipoints()[i]->setPlaneToRunway(airplane);
        }
    }
}
