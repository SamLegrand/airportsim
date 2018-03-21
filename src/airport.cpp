//
// Created by sam on 01.03.18.
//

#include "airport.h"

void Airport::setName(const string &name) {
    Airport::name = name;
}

void Airport::setIata(const string &iata) {
    Airport::iata = iata;
}

void Airport::setCallsign(const string &callsign) {
    Airport::callsign = callsign;
}

void Airport::setRunways(const vector<Runway *> &runways) {
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

const string &Airport::getName() const {
    return name;
}

const string &Airport::getIata() const {
    return iata;
}

const string &Airport::getCallsign() const {
    return callsign;
}

const vector<Runway *> &Airport::getRunways() const {
    return runways;
}

const int Airport::getGates() const {
    return (int)gates.size();
}

const int &Airport::getPassengers() const {
    return passengers;
}

void Airport::printInfo(ofstream &output) const {
    output << "Airport: " << name << " (" << iata << ")" << endl;
    output << " -> gates: " << gates.size() << endl;
    output << " -> runways: " << runways.size() << endl;
}

int Airport::getAvailableGate() {
    REQUIRE(!gates.empty(), "There haven't been any gates added.");
    for (unsigned int i = 0; i < gates.size(); i++) {
        if(gates[i] == NULL){
            return i + 1;
        }
    }
    return -1;
}

void Airport::addPlaneToGate(Airplane *airplane, int gate) {
    REQUIRE(gate > 0 && (unsigned)gate < this->gates.size(), "Gate should be a valid value.");
    gates[gate - 1] = airplane;
    ENSURE(gates[gate - 1] == airplane, "Plane wasn't added to correct gate.");
}

int Airport::findPlaneInGate(Airplane *airplane) {
    REQUIRE(!gates.empty(), "There haven't been any gates added.");
    for (unsigned int i = 0; i < gates.size(); ++i) {
        if(gates[i] == airplane){
            return i + 1;
        }
    }
    return -1;
}

void Airport::removePlaneFromGate(Airplane *airplane) {
    REQUIRE(!gates.empty(), "There haven't been any gates added.");
    for (unsigned int i = 0; i < gates.size(); i++) {
        if(gates[i] == airplane){
            gates[i] = NULL;
            ENSURE(gates[i] == NULL, "Plane wasn't correctly removed from gate.");
        }
    }
}

void Airport::addRunway(Runway *_runway) {
    REQUIRE(_runway->airplane == NULL, "Runway isn't properly initialised.");
    runways.push_back(_runway);
}

void Airport::addPlaneToRunway(Airplane *airplane, int runway) {
    REQUIRE(runway > 0 && (unsigned)runway < this->runways.size(), "Runway should be a valid value.");
    runways[runway]->airplane = airplane;
}

void Airport::removePlaneFromRunway(Airplane *airplane) {
    REQUIRE(!runways.empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); i++) {
        if(runways[i]->airplane == airplane){
            runways[i]->airplane = NULL;
            ENSURE(runways[i] == NULL, "Plane wasn't correctly removed from runway.");
        }
    }
}

Runway *Airport::getAvailableRunway() {
    REQUIRE(!runways.empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); i++) {
        if(runways[i]->airplane == NULL){
            return runways[i];
        }
    }
    return NULL;
}

Runway *Airport::findPlaneInRunway(Airplane* airplane) {
    REQUIRE(!runways.empty(), "There haven't been any runways added.");
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->airplane == airplane){
            return runways[i];
        }
    }
    return NULL;
}
