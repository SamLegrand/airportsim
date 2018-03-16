//
// Created by sam on 01.03.18.
//

#include "runway.h"

void Runway::setName(const string &name) {
    Runway::name = name;
    available = true;
}

const string Runway::getName() const {
    return name;
}

bool Runway::isEmpty() const {
    return available;
}
