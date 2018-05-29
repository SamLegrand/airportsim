//
// Created by sam on 01.03.18.
//

#include "airplane.h"

Airplane::Airplane(){
    time = 0;
    communicating = true;
    squawk = 0;
    initCheck = this;
    ENSURE(this->properlyInitialized(), "Plane wasn't properly initialized.");
}

Airplane::Airplane(Airplane* airplane){
    REQUIRE(airplane->properlyInitialized(), "Plane wasn't properly initialized.");
    number = airplane->getNumber();
    model = airplane->getModel();
    type = airplane->getType();
    engine = airplane->getEngine();
    fuel = airplane->getFuel();
    height = airplane->getHeight();
    squawk = airplane->getSquawk();
    communicating = airplane->isCommunicating();
    time = airplane->getTime();
    passengers = airplane->getPassengers();
    callsign = airplane->getCallsign();
    status = airplane->getStatus();
    initCheck = this;
    delete airplane;
    ENSURE(this->properlyInitialized(), "Plane wasn't properly initialized.");
}

Airplane::~Airplane(){
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
}

bool Airplane::properlyInitialized() {
    return initCheck == this;
}

void Airplane::setNumber(const std::string &number) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::number = number;
}

void Airplane::setCallsign(const std::string &callsign){
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::callsign = callsign;
}

void Airplane::setModel(const std::string &model) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::model = model;
}

void Airplane::setStatus(const std::string &status) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::status = status;
}

void Airplane::setPassengers(int passengers) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::passengers = passengers;
}

void Airplane::setFuel(int fuel) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::fuel = fuel;
}

void Airplane::setHeight(int height) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::height = height;
}

const std::string &Airplane::getNumber() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return number;
}

const std::string &Airplane::getCallsign() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return callsign;
}

const std::string &Airplane::getModel() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return model;
}

const std::string &Airplane::getStatus() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return status;
}

int Airplane::getPassengers() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return passengers;
}

int Airplane::getFuel() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return fuel;
}

int Airplane::getHeight() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return height;
}

void Airplane::printInfo(std::ofstream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    output << "Airplane: " << callsign << " (" << number << ")" << std::endl;
    output << " -> model: " << model << std::endl;
}

void Airplane::approach(std::ostream &output, const std::string& airport) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Approaching", "Plane has to the be in correct state.");
    consumeFuel();
    height = 10000;
    output << callsign << " is approaching " << airport << " at " << height << " ft." << std::endl;
    status = "Descending to 5k";
    ENSURE(this->getStatus() == "Descending to 5k", "Plane should be set to the correct state.");
}

void Airplane::flyWaitPattern(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Flying wait pattern", "Plane has to the be in correct state.");
    consumeFuel();
    output << callsign << " is flying wait pattern at " << height << " ft." << std::endl;
    ENSURE(this->getStatus() == "Flying wait pattern", "Plane should be set to the correct state.");
}

void Airplane::descendTo5k(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Descending to 5k", "Plane has to the be in correct state.");
    consumeFuel();
    time += 1;
    if (engine == "jet" || time == 2) {
        height = height - 1000;
        output << callsign << " descended to " << height << " ft." << std::endl;
        time = 0;
    }
    if (height == 5000) {
        status = "Flying wait pattern";
    }
    ENSURE(this->getStatus() == "Flying wait pattern" || this->getStatus() == "Descending to 5k", "Plane should be set to the correct state.");
}

void Airplane::descendTo3k(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Descending to 3k", "Plane has to the be in correct state.");
    consumeFuel();
    time += 1;
    if (engine == "jet" || time == 2) {
        height = height - 1000;
        output << callsign << " descended to " << height << " ft." << std::endl;
        time = 0;
    }
    if (height == 3000) {
        status = "Flying wait pattern";
    }
    ENSURE(this->getStatus() == "Flying wait pattern" || this->getStatus() == "Descending to 3k", "Plane should be set to the correct state.");
}

void Airplane::finalapproach(std::ostream &output, const std::string &airport, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Final Approach", "Plane has to the be in correct state.");
    consumeFuel();
    time += 1;
    if (engine == "jet" || time == 2) {
        height = height - 1000;
        output << callsign << " descended to " << height << " ft." << std::endl;
        time = 0;
    }
    if (height == 1000) {
        status = "Landing";
    }
    ENSURE(this->getStatus() == "Final Approach" || this->getStatus() == "Landing", "Plane should be set to the correct state.");
}

void Airplane::land(std::ostream &output, const std::string& airport, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Landing", "Plane has to the be in correct state.");
    consumeFuel();
    time += 1;
    if (time == 1) {
        output << callsign << " is landing at " << airport << " on runway " << runway << std::endl;
    }
    else if (time == 2) {
        status = "Landed";
        height = 0;
        time = 0;
    }
    ENSURE(this->getStatus() == "Landed" || this->getStatus() == "Landing", "Plane should be set to the correct state.");
}

void Airplane::landed(std::ostream &output, const std::string& airport, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Landed", "Plane has to the be in correct state.");
    output << callsign << " has landed at " << airport << " on runway " << runway << std::endl;
    ENSURE(this->getStatus() == "Landed", "Plane should be set to the correct state.");
}

void Airplane::taxiToGate(std::ostream &output, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Taxiing to Gate", "Plane has to the be in correct state.");
    output << callsign << " is standing at gate " << gate << "." << std::endl;
    status = "Unboarding Plane";
    ENSURE(this->getStatus() == "Unboarding Plane", "Plane should be set to the correct state.");
}

void Airplane::refuelPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Refueling Plane", "Plane has to the be in correct state.");
    output << callsign << " has been refueled" << std::endl;
    status = "Boarding Plane";
    ENSURE(this->getStatus() == "Boarding Plane", "Plane should be set to the correct state.");
}

void Airplane::stand(std::ostream &output, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Standing at Gate", "Plane has to the be in correct state.");
    height = 0;
    output << callsign << " is standing at gate " << gate << std::endl;
    ENSURE(this->getStatus() == "Standing at Gate", "Plane should be set to the correct state.");
}

void Airplane::taxiToRunway(std::ostream &output, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Taxiing to Runway", "Plane has to the be in correct state.");
    output << callsign << " is waiting at runway " << runway << std::endl;
    status = "Ready for Takeoff";
    ENSURE(this->getStatus() == "Ready for Takeoff", "Plane should be set to the correct state.");
}

void Airplane::readyForTakeoff(std::ostream &output, const std::string &airport, const std::string &runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Ready for Takeoff", "Plane has to the be in correct state.");
    output << callsign << " is ready for takeoff at " << airport << " on runway " << runway << std::endl;
    status = "Taking Off";
    ENSURE(this->getStatus() == "Taking Off", "Plane should be set to the correct state.");
}

void Airplane::takeOff(std::ostream &output, const std::string& airport, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Taking Off", "Plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        height = 0;
        output << callsign << " is taking off at " << airport << " on runway " << runway << std::endl;
    }
    else if (engine == "jet" || time == 3) {
        status = "Ascending";
        time = 0;
    }
    ENSURE(this->getStatus() == "Ascending" || this->getStatus() == "Taking Off", "Plane should be set to the correct state.");
}

void Airplane::ascend(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Ascending", "Plane has to the be in correct state.");
    consumeFuel();
    time += 1;
    if (engine == "jet" || time == 2) {
        height = height + 1000;
        output << callsign << " ascended to " << height << " ft." << std::endl;
        time = 0;
    }
    if(height == 5000) {
        status = "Leaving Airport";
    }
    ENSURE(this->getStatus() == "Leaving Airport" || this->getStatus() == "Ascending", "Plane should be set to the correct state.");
}

void Airplane::leaveAirport(std::ostream &output, const std::string& airport) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Leaving Airport", "Plane has to the be in correct state.");
    consumeFuel();
    output << callsign << " has left " << airport << std::endl;
    height = 10000;
    status = "Travelling";
    ENSURE(this->getStatus() == "Travelling", "Plane should be set to the correct state.");
}

const std::string &Airplane::getType() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return type;
}

void Airplane::setType(const std::string &type) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::type = type;
}

const std::string &Airplane::getEngine() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return engine;
}

void Airplane::setEngine(const std::string &engine) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::engine = engine;
}

bool Airplane::isAtGate() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return Airplane::status == "Unboarding Plane" ||
           Airplane::status == "Checking Plane" ||
           Airplane::status == "Refueling Plane" ||
           Airplane::status == "Boarding Plane" ||
           Airplane::status == "Standing at Gate" ||
           Airplane::status == "Taxiing to Runway";
}

bool Airplane::isAtRunway() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return Airplane::status == "Landed" ||
           Airplane::status == "Taxiing to Gate" ||
           Airplane::status == "Ready for Takeoff";
}

int Airplane::getTime() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return time;
}

void Airplane::setTime(int time) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::time = time;
}

bool Airplane::isCommunicating() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return communicating;
}

void Airplane::setCommunication(bool communication) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::communicating = communication;
}

int Airplane::getSquawk() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return squawk;
}

void Airplane::setSquawk(int squawk) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::squawk = squawk;
}

const std::string &Airplane::getDestination() const {
    return destination;
}

void Airplane::setDestination(const std::string &destination) {
    Airplane::destination = destination;
}

int Airplane::getDeparture() const {
    return departure;
}

void Airplane::setDeparture(int departure) {
    Airplane::departure = departure;
}

int Airplane::getArrival() const {
    return arrival;
}

void Airplane::setArrival(int arrival) {
    Airplane::arrival = arrival;
}

int Airplane::getInterval() const {
    return interval;
}

void Airplane::setInterval(int interval) {
    Airplane::interval = interval;
}
