//
// Created by sam on 27.04.18.
//

#include "Taxipoint.h"

Taxipoint::Taxipoint(const std::string &name) {
    Taxipoint::name = name;
    planeToGate = NULL;
    planeToRunway = NULL;
    initCheck = this;
}

bool Taxipoint::properlyInitialized(){
    return initCheck == this;
}

const std::string &Taxipoint::getName() const {
    return name;
}

void Taxipoint::setName(const std::string &name) {
    Taxipoint::name = name;
}

Airplane *Taxipoint::getPlaneToGate() const {
    return planeToGate;
}

void Taxipoint::setPlaneToGate(Airplane *planeToGate) {
    Taxipoint::planeToGate = planeToGate;
}

Airplane *Taxipoint::getPlaneToRunway() const {
    return planeToRunway;
}

void Taxipoint::setPlaneToRunway(Airplane *planeToRunway) {
    Taxipoint::planeToRunway = planeToRunway;
}
