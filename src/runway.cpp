//
// Created by lena on 3/29/18.
//

#include "runway.h"

Runway::Runway() {
    Runway::name = "";
    Runway::airplane = NULL;
    Runway::crossingToGate = NULL;
    Runway::crossingToRunway = NULL;
    Runway::taxipointToGate = NULL;
    Runway::taxipointToRunway = NULL;
    Runway::initCheck = this;
}

bool Runway::properlyInitialized(){
    return Runway::initCheck == this;
}

const std::string &Runway::getName() const {
    return name;
}

void Runway::setName(const std::string &name) {
    Runway::name = name;
}

Airplane *Runway::getAirplane() const {
    return airplane;
}

void Runway::setAirplane(Airplane *airplane) {
    Runway::airplane = airplane;
}

const std::string &Runway::getType() const {
    return type;
}

void Runway::setType(const std::string &type) {
    Runway::type = type;
}

int Runway::getLength() const {
    return length;
}

void Runway::setLength(int length) {
    Runway::length = length;
}

bool Runway::ableToCross() {
    return !airplane || airplane->getStatus() == "Ready for Takeoff" || airplane->getStatus() == "Taxiing" || airplane->getStatus() == "Crashlanding";
}

Airplane *Runway::getTaxipointToRunway() const {
    return taxipointToRunway;
}

void Runway::setTaxipointToRunway(Airplane *taxipointToRunway) {
    Runway::taxipointToRunway = taxipointToRunway;
}

Airplane *Runway::getTaxipointToGate() const {
    return taxipointToGate;
}

void Runway::setTaxipointToGate(Airplane *taxipointToGate) {
    Runway::taxipointToGate = taxipointToGate;
}

Airplane *Runway::getCrossingToRunway() const {
    return crossingToRunway;
}

void Runway::setCrossingToRunway(Airplane *crossingToRunway) {
    Runway::crossingToRunway = crossingToRunway;
}

Airplane *Runway::getCrossingToGate() const {
    return crossingToGate;
}

void Runway::setCrossingToGate(Airplane *crossingToGate) {
    Runway::crossingToGate = crossingToGate;
}

const std::string &Runway::getTaxipoint() const {
    return taxipoint;
}

void Runway::setTaxipoint(const std::string &taxipoint) {
    Runway::taxipoint = taxipoint;
}
