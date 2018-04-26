//
// Created by lena on 3/29/18.
//

#include "runway.h"

Runway::Runway() {
    Runway::name = "";
    Runway::airplane = NULL;
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

void Runway::addTaxipoint(std::string taxipoint) {
    Runway::taxipoints.push_back(taxipoint);
}

void Runway::addCrossing(std::string crossing){
    Runway::crossings.push_back(crossing);
}

const std::vector<std::string> &Runway::getTaxipoints() const {
    return taxipoints;
}

const std::vector<std::string> &Runway::getCrossings() const {
    return crossings;
}

Airplane *Runway::getAirplaneCrossing() const {
    return airplaneCrossing;
}

void Runway::setAirplaneCrossing(Airplane *airplaneCrossing) {
    Runway::airplaneCrossing = airplaneCrossing;
}
