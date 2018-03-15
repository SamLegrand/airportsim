//
// Created by sam on 01.03.18.
//

#include "runway.h"

void Runway::setName(string _name) {
    name = _name;
    available = true;
}

void Runway::printInfo() {
    cout << name << endl;
}

string Runway::getName() {
    return name;
}

bool Runway::isEmpty() {
    return available;
}
