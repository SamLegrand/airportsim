//
// Created by sam on 01.03.18.
//

#include "airport.h"

void Airport::setName(string _name) {
    name = _name;
}

void Airport::setIata(string _iata) {
    iata = _iata;
}

void Airport::setCallsign(string _callsign) {
    callsign = _callsign;
}

void Airport::setGates(int _gate) {
    gates.reserve(_gate);
    for (int i=0; i<_gate; i++) {
        gates.push_back(NULL);
    }
}

void Airport::setPassengers(int _passengers) {
    passengers = _passengers;
}

void Airport::addRunway(Runway *_runway) {
    runways.push_back(_runway);
}

void Airport::printInfo(ofstream &output){
    output << "Airport: " << name << " (" << iata << ")" << endl;
    output << " -> gates: " << gates.size() << endl;
    output << " -> runways: " << runways.size() << endl;
}

void Airport::printTestingInfo(){
    cout << name << endl;
    cout << iata << endl;
    cout << callsign << endl;
    cout << gates.size() << endl;
    cout << passengers << endl;
}

string Airport::getName() {
    return name;
}

string Airport::getIata() {
    return iata;
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
