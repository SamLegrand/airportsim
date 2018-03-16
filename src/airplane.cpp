//
// Created by sam on 01.03.18.
//

#include "airplane.h"

void Airplane::setNumber(const string &number) {
    Airplane::number = number;
}

void Airplane::setCallsign(const string &callsign){
    Airplane::callsign = callsign;
}

void Airplane::setModel(const string &model) {
    Airplane::model = model;
}

void Airplane::setStatus(const string &status) {
    Airplane::status = status;
}

void Airplane::setPassengers(int passengers) {
    Airplane::passengers = passengers;
}

void Airplane::setFuel(int fuel) {
    Airplane::fuel = fuel;
}

void Airplane::setHeight(int height) {
    Airplane::height = height;
}

const string &Airplane::getNumber() const {
    return number;
}

const string &Airplane::getCallsign() const {
    return callsign;
}

const string &Airplane::getModel() const {
    return model;
}

const string &Airplane::getStatus() const {
    return status;
}

int Airplane::getPassengers() const {
    return passengers;
}

int Airplane::getFuel() const {
    return fuel;
}

int Airplane::getHeight() const {
    return height;
}

void Airplane::printInfo(ofstream &output) {
    output << "Airplane: " << callsign << " (" << number << ")" << endl;
    output << " -> model: " << model << endl;
}

void Airplane::approach(ostream &output, const string& airport) {
    height = 10000;
    output << callsign << " is approaching " << airport << " at " << height << " ft." << endl;
    status = "Descending";
}

void Airplane::descend(ostream &output) {
    height = height - 1000;
    output << callsign << " descended to " << height << " ft." << endl;
    if (height == 1000) {
        status = "Landing";
    }
}

void Airplane::land(ostream &output, const string& airport, const string& runway) {
    output << callsign << " is landing at " << airport << " on runway " << runway << endl;
    status = "Landed";
    height = 0;
}

void Airplane::landed(ostream &output, const string& airport, const string& runway) {
    output << callsign << " has landed at " << airport << " on runway " << runway << endl;
    status = "Awaiting Taxi";
}

void Airplane::taxiToGate(ostream &output, int gate) {
    output << callsign << " is taxiing to Gate " << gate << "." << endl;
    status = "Taxiing to Gate";
}

void Airplane::stand(ostream &output, int gate) {
    height = 0;
    output << callsign << " is standing at Gate " << gate << "." << endl;
    status = "Standing at Gate";
}

void Airplane::unboardPlane(ostream &output, const string& airport, int gate) {
    output << passengers << " passengers exited " << callsign << " at gate " << gate << " of " << airport << endl;
    status = "Unboarded Plane";
}

void Airplane::checkPlane(ostream &output) {
    output << callsign << " has been checked for technical malfunctions" << endl;
    status = "Checked Plane";
}

void Airplane::refuelPlane(ostream &output) {
    output << callsign << " has been refueled" << endl;
    status = "Refueled Plane";
}

void Airplane::boardPlane(ostream &output, const string& airport, int gate) {
    output << passengers << " boarded " << callsign << " at gate " << gate << " of " << airport << endl;
    status = "Boarded Plane";
}

void Airplane::taxiToRunway(ostream &output, const string& runway) {
    output << callsign << " is taxiing to runway " << runway << endl;
    status = "Taxiing to Runway";
}

void Airplane::takeOff(ostream &output, const string& airport, const string& runway) {
    output << callsign << " is taking off at " << airport << " on runway " << runway << endl;
    status = "Ascending";
}

void Airplane::ascend(ostream &output) {
    height = height + 1000;
    output << callsign << " ascended to " << height << " ft." << endl;
    if(height == 5000) {
        status = "Leaving Airport";
    }
}

void Airplane::leaveAirport(ostream &output, const string& airport) {
    output << callsign << " has left " << airport << endl;
    status = "Travelling";
}