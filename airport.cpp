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

void Airport::setGates(int _gates) {
    gates = _gates;
}

void Airport::setPassengers(int _passengers) {
    passengers = _passengers;
}

void Airport::addRunway(Runway *_runway) {
    runways.push_back(_runway);
}


void Airport::printInfo(){
    cout << "Airport: " << name << " (" << iata << ")" << endl;
    cout << " -> gates: " << gates << endl;
    cout << " -> runways: " << runways.size() << endl;
}

void Airport::printTestingInfo(){
    cout << name << endl;
    cout << iata << endl;
    cout << callsign << endl;
    cout << gates << endl;
    cout << passengers << endl;
}
