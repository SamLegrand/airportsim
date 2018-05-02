//
// Created by lena on 3/29/18.
//

#include "runway.h"

Runway::Runway() {
    Runway::name = "";
    Runway::airplane = NULL;
    Runway::crossing = NULL;
    Runway::taxipointToGate = NULL;
    Runway::taxipointToRunway = NULL;
    Runway::initCheck = this;
}

bool Runway::properlyInitialized(){
    return Runway::initCheck == this;
}

const std::string &Runway::getName() {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    return name;
}

void Runway::setName(const std::string &name) {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    Runway::name = name;
}

Airplane *Runway::getAirplane() {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    return airplane;
}

void Runway::setAirplane(Airplane *airplane) {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    Runway::airplane = airplane;
}

const std::string &Runway::getType() {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    return type;
}

void Runway::setType(const std::string &type) {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    Runway::type = type;
}

int Runway::getLength() {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    return length;
}

void Runway::setLength(int length) {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    Runway::length = length;
}

bool Runway::ableToCross() {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    return (!airplane || airplane->getStatus() == "Ready for Takeoff" || airplane->getStatus() == "Taxiing to Runway" || airplane->getStatus() == "Waiting to cross to Runway" || airplane->getStatus() == "Crossing to Runway" || airplane->getStatus() == "Crashlanding") && !crossing;
}

Airplane *Runway::getTaxipointToRunway() {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    return taxipointToRunway;
}

void Runway::setTaxipointToRunway(Airplane *taxipointToRunway) {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    Runway::taxipointToRunway = taxipointToRunway;
    ENSURE(this->getTaxipointToRunway() == taxipointToRunway, "Plane wasn't correctly added to taxipointToRunway");
}

Airplane *Runway::getTaxipointToGate() {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    return taxipointToGate;
}

void Runway::setTaxipointToGate(Airplane *taxipointToGate) {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    Runway::taxipointToGate = taxipointToGate;
    ENSURE(this->getTaxipointToGate() == taxipointToGate, "Plane wasn't correctly added to taxipointToGate");
}

Airplane *Runway::getAirplaneCrossing() {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    return crossing;
}

void Runway::setAirplaneCrossing(Airplane *crossing){
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    Runway::crossing = crossing;
    ENSURE(this->getAirplaneCrossing() == crossing, "Plane wasn't correctly added to crossing");
}

const std::string &Runway::getTaxipoint() {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    return taxipoint;
}

void Runway::setTaxipoint(const std::string &taxipoint) {
    REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
    Runway::taxipoint = taxipoint;
    ENSURE(this->getTaxipoint() == taxipoint, "Taxipoint name wasn't set properly.");
}
