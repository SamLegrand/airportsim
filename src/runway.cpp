//
// Created by lena on 3/29/18.
//

#include "runway.h"

Runway::Runway() {
    Runway::name = "";
    Runway::airplane = NULL;
}

const string &Runway::getName() const {
    return name;
}

void Runway::setName(const string &name) {
    Runway::name = name;
}

Airplane *Runway::getAirplane() const {
    return airplane;
}

void Runway::setAirplane(Airplane *airplane) {
    Runway::airplane = airplane;
}
