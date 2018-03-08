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

void Airport::addGate(Gate* _gate) {
    gates.push_back(_gate);
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
    return runways[0];
}
