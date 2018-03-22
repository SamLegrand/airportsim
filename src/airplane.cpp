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
    REQUIRE(this->getStatus() == "Approaching", "Plane wasn't in correct state.");
    height = 10000;
    output << callsign << " is approaching " << airport << " at " << height << " ft." << endl;
    status = "Descending";
    ENSURE(this->getStatus() == "Descending", "Plane hasn't been set to the correct state.");
}

void Airplane::descend(ostream &output) {
    REQUIRE(this->getStatus() == "Descending", "Plane wasn't in correct state.");
    height = height - 1000;
    output << callsign << " descended to " << height << " ft." << endl;
    if (height == 1000) {
        status = "Landing";
    }
    ENSURE(this->getStatus() == "Landing" || this->getStatus() == "Descending", "Plane hasn't been set to the correct state.");
}

void Airplane::land(ostream &output, const string& airport, const string& runway) {
    REQUIRE(this->getStatus() == "Landing", "Plane wasn't in correct state.");
    output << callsign << " is landing at " << airport << " on runway " << runway << endl;
    status = "Landed";
    height = 0;
    ENSURE(this->getStatus() == "Landed", "Plane hasn't been set to the correct state.");
}

void Airplane::landed(ostream &output, const string& airport, const string& runway) {
    REQUIRE(this->getStatus() == "Landed", "Plane wasn't in correct state.");
    output << callsign << " has landed at " << airport << " on runway " << runway << endl;
    status = "Taxiing to Gate";
    ENSURE(this->getStatus() == "Taxiing to Gate", "Plane hasn't been set to the correct state.");
}

void Airplane::taxiToGate(ostream &output, int gate) {
    REQUIRE(this->getStatus() == "Taxiing to Gate", "Plane wasn't in correct state.");
    output << callsign << " is taxiing to Gate " << gate << endl;
    status = "Unboarding Plane";
    ENSURE(this->getStatus() == "Unboarding Plane", "Plane hasn't been set to the correct state.");
}

void Airplane::unboardPlane(ostream &output, const string& airport, int gate) {
    REQUIRE(this->getStatus() == "Unboarding Plane", "Plane wasn't in correct state.");
    output << passengers << " passengers exited " << callsign << " at gate " << gate << " of " << airport << endl;
    status = "Checking Plane";
    ENSURE(this->getStatus() == "Checking Plane", "Plane hasn't been set to the correct state.");
}

void Airplane::checkPlane(ostream &output) {
    REQUIRE(this->getStatus() == "Checking Plane", "Plane wasn't in correct state.");
    output << callsign << " has been checked for technical malfunctions" << endl;
    status = "Refueling Plane";
    ENSURE(this->getStatus() == "Refueling Plane", "Plane hasn't been set to the correct state.");
}

void Airplane::refuelPlane(ostream &output) {
    REQUIRE(this->getStatus() == "Refueling Plane", "Plane wasn't in correct state.");
    output << callsign << " has been refueled" << endl;
    status = "Boarding Plane";
    ENSURE(this->getStatus() == "Boarding Plane", "Plane hasn't been set to the correct state.");
}

void Airplane::boardPlane(ostream &output, const string& airport, int gate) {
    REQUIRE(this->getStatus() == "Boarding Plane", "Plane wasn't in correct state.");
    output << passengers << " passengers boarded " << callsign << " at gate " << gate << " of " << airport << endl;
    status = "Standing at Gate";
    ENSURE(this->getStatus() == "Standing at Gate", "Plane hasn't been set to the correct state.");
}

void Airplane::stand(ostream &output, int gate) {
    REQUIRE(this->getStatus() == "Standing at Gate", "Plane wasn't in correct state.");
    height = 0;
    output << callsign << " is standing at Gate " << gate << endl;
    status = "Taxiing to Runway";
    ENSURE(this->getStatus() == "Taxiing to Runway", "Plane hasn't been set to the correct state.");
}

void Airplane::taxiToRunway(ostream &output, const string& runway) {
    REQUIRE(this->getStatus() == "Taxiing to Runway", "Plane wasn't in correct state.");
    output << callsign << " is taxiing to runway " << runway << endl;
    status = "Taking Off";
    ENSURE(this->getStatus() == "Taking Off", "Plane hasn't been set to the correct state.");
}

void Airplane::takeOff(ostream &output, const string& airport, const string& runway) {
    REQUIRE(this->getStatus() == "Taking Off", "Plane wasn't in correct state.");
    height = 0;
    output << callsign << " is taking off at " << airport << " on runway " << runway << endl;
    status = "Ascending";
    ENSURE(this->getStatus() == "Ascending", "Plane hasn't been set to the correct state.");
}

void Airplane::ascend(ostream &output) {
    REQUIRE(this->getStatus() == "Ascending", "Plane wasn't in correct state.");
    height = height + 1000;
    output << callsign << " ascended to " << height << " ft." << endl;
    if(height == 5000) {
        status = "Leaving Airport";
    }
    ENSURE(this->getStatus() == "Leaving Airport" || this->getStatus() == "Ascending", "Plane hasn't been set to the correct state.");
}

void Airplane::leaveAirport(ostream &output, const string& airport) {
    REQUIRE(this->getStatus() == "Leaving Airport", "Plane wasn't in correct state.");
    output << callsign << " has left " << airport << endl;
    status = "Travelling";
    ENSURE(this->getStatus() == "Travelling", "Plane hasn't been set to the correct state.");
}