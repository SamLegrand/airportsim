//
// Created by sam on 01.03.18.
//

#include "runway.h"

void Runway::setName(string _name) {
    name = _name;
}

void Runway::setAirport(string _airport) {
    airport = _airport;
}

void Runway::printInfo() {
    cout << name << endl;
    cout << airport << endl;
}