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

const string &Runway::getType() const {
    return type;
}

void Runway::setType(const string &type) {
    Runway::type = type;
}

int Runway::getLength() const {
    return length;
}

void Runway::setLength(int length) {
    Runway::length = length;
}

void Runway::addTaxipoint(string taxipoint) {
    Runway::taxipoints.push_back(taxipoint);
}

void Runway::addCrossing(string crossing){
    Runway::crossings.push_back(crossing);
}
