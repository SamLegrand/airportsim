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

const vector<Airplane *> &Airport::getGates() const {
    return gates;
}

const int &Airport::getPassengers() const {
    return passengers;
}

void Airport::addRunway(Runway *_runway) {
    runways.push_back(_runway);
}

void Airport::printInfo(ofstream &output) const {
    output << "Airport: " << name << " (" << iata << ")" << endl;
    output << " -> gates: " << gates.size() << endl;
    output << " -> runways: " << runways.size() << endl;
}

Runway *Airport::getAvailableRunway() {
    for (unsigned int i = 0; i < runways.size(); ++i) {
        if(runways[i]->isEmpty()){
            return runways[i];
        }
    }
    return NULL;
}

int Airport::getAvailableGate() {
    for (unsigned int i = 0; i < gates.size(); ++i) {
        if(gates[i] != NULL){
            return i + 1;
        }
    }
    return -1;
}

void Airport::addPlane(Airplane *airplane, int gate) {
    gates[gate] = airplane;
}

void Airport::removePlane(Airplane *airplane) {
    for (unsigned int i = 0; i < gates.size(); ++i) {
        if(gates[i] == airplane){
            gates[i] = NULL;
        }
    }
}
