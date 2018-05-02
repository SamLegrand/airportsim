//
// Created by sam on 01.03.18.
//

#include "airplane.h"

Airplane::Airplane(){
    time = 0;
    communicating = true;
    squawk = 0;
    initCheck = this;
}

bool Airplane::properlyInitialized(){
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
    REQUIRE(this->getStatus() == "Approaching", "Plane wasn't in correct state.");
    height = 10000;
    output << callsign << " is approaching " << airport << " at " << height << " ft." << std::endl;
    status = "Descending to 5k";
    ENSURE(this->getStatus() == "Descending to 5k", "Plane hasn't been set to the correct state.");
}

void Airplane::flyWaitPattern(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Flying wait pattern", "Plane wasn't in correct state.");
    output << callsign << " is flying wait pattern at " << height << " ft." << std::endl;
    ENSURE(this->getStatus() == "Flying wait pattern", "Plane hasn't been set to the correct state.");
}

void Airplane::descendTo5k(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Descending to 5k", "Plane wasn't in correct state.");
    time += 1;
    if (engine == "jet" || time == 2) {
        height = height - 1000;
        output << callsign << " descended to " << height << " ft." << std::endl;
        time = 0;
    }
    if (height == 5000) {
        status = "Flying wait pattern";
    }
    ENSURE(this->getStatus() == "Flying wait pattern" || this->getStatus() == "Descending to 5k", "Plane hasn't been set to the correct state.");
}

void Airplane::descendTo3k(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Descending to 3k", "Plane wasn't in correct state.");
    time += 1;
    if (engine == "jet" || time == 2) {
        height = height - 1000;
        output << callsign << " descended to " << height << " ft." << std::endl;
        time = 0;
    }
    if (height == 3000) {
        status = "Flying wait pattern";
    }
    ENSURE(this->getStatus() == "Flying wait pattern" || this->getStatus() == "Descending to 3k", "Plane hasn't been set to the correct state.");
}

void Airplane::finalapproach(std::ostream &output, const std::string &airport, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Final Approach", "Plane wasn't in correct state.");
    time += 1;
    if (engine == "jet" || time == 2) {
        height = height - 1000;
        output << callsign << " descended to " << height << " ft." << std::endl;
        time = 0;
    }
    if (height == 1000) {
        status = "Landing";
    }
    ENSURE(this->getStatus() == "Final Approach" || this->getStatus() == "Landing", "Plane hasn't been set to the correct state.");
}

void Airplane::land(std::ostream &output, const std::string& airport, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Landing", "Plane wasn't in correct state.");
    time += 1;
    if (time == 1) {
        output << callsign << " is landing at " << airport << " on runway " << runway << std::endl;
    }
    else if (time == 2) {
        status = "Landed";
        height = 0;
        time = 0;
    }
    ENSURE(this->getStatus() == "Landed" || this->getStatus() == "Landing", "Plane hasn't been set to the correct state.");
}

void Airplane::landed(std::ostream &output, const std::string& airport, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Landed", "Plane wasn't in correct state.");
    output << callsign << " has landed at " << airport << " on runway " << runway << std::endl;
    ENSURE(this->getStatus() == "Landed", "Plane hasn't been set to the correct state.");
}

void Airplane::taxiToGate(std::ostream &output, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Taxiing to Gate", "Plane wasn't in correct state.");
    output << callsign << " is standing at gate " << gate << "." << std::endl;
    status = "Unboarding Plane";
    ENSURE(this->getStatus() == "Unboarding Plane", "Plane hasn't been set to the correct state.");
}

void Airplane::unboardPlane(std::ostream &output, const std::string& airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Unboarding Plane", "Plane wasn't in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers exited " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    else if ((time == 5 && size == "small") || (time == 10 && size == "medium") || time == 15) {
        status = "Checking Plane";
        time = 0;
    }
    ENSURE(this->getStatus() == "Checking Plane" || this->getStatus() == "Unboarding Plane", "Plane hasn't been set to the correct state.");
}

void Airplane::checkPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Checking Plane", "Plane wasn't in correct state.");
    time += 1;
    if (time == 1) {
        output << callsign << " has been checked for technical malfunctions" << std::endl;
    }
    if (size == "small" || (time == 2 && size == "medium") || time == 3) {
        status = "Refueling Plane";
        time = 0;
    }
    ENSURE(this->getStatus() == "Refueling Plane" || this->getStatus() == "Checking Plane", "Plane hasn't been set to the correct state.");
}

void Airplane::refuelPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Refueling Plane", "Plane wasn't in correct state.");
    output << callsign << " has been refueled" << std::endl;
    status = "Boarding Plane";
    ENSURE(this->getStatus() == "Boarding Plane", "Plane hasn't been set to the correct state.");
}

void Airplane::boardPlane(std::ostream &output, const std::string& airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Boarding Plane", "Plane wasn't in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers boarded " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    else if ((time == 5 && size == "small") || (time == 10 && size == "medium") || time == 15) {
        status = "Standing at Gate";
        time = 0;
    }
    ENSURE(this->getStatus() == "Standing at Gate" || this->getStatus() == "Boarding Plane", "Plane hasn't been set to the correct state.");
}

void Airplane::stand(std::ostream &output, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Standing at Gate", "Plane wasn't in correct state.");
    height = 0;
    output << callsign << " is standing at gate " << gate << std::endl;
    ENSURE(this->getStatus() == "Standing at Gate", "Plane hasn't been set to the correct state.");
}

void Airplane::pushBack(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Pushing back", "Plane wasn't in correct state.");
    time += 1;
    if (time == 1) {
        output << callsign << " starting pushback" << std::endl;
    }
    if (size == "small" || (time == 2 && size == "medium") || time == 3) {
        time = 0;
        status = "Taxiing to Runway";
    }
    ENSURE(this->getStatus() == "Taxiing to Runway" || this->getStatus() == "Pushing back", "Plane hasn't been set to the correct state.");
}

void Airplane::taxiToRunway(std::ostream &output, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Taxiing to Runway", "Plane wasn't in correct state.");
    output << callsign << " is waiting at runway " << runway << std::endl;
    status = "Ready for Takeoff";
    ENSURE(this->getStatus() == "Ready for Takeoff", "Plane hasn't been set to the correct state.");
}

void Airplane::readyForTakeoff(std::ostream &output, const std::string &airport, const std::string &runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Ready for Takeoff", "Plane wasn't in correct state.");
    output << callsign << " is ready for takeoff at " << airport << " on runway " << runway << std::endl;
    status = "Taking Off";
    ENSURE(this->getStatus() == "Taking Off", "Plane hasn't been set to the correct state.");
}

void Airplane::takeOff(std::ostream &output, const std::string& airport, const std::string& runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Taking Off", "Plane wasn't in correct state.");
    time += 1;
    if (time == 1) {
        height = 0;
        output << callsign << " is taking off at " << airport << " on runway " << runway << std::endl;
    }
    else if (engine == "jet" || time == 3) {
        status = "Ascending";
        time = 0;
    }
    ENSURE(this->getStatus() == "Ascending" || this->getStatus() == "Taking Off", "Plane hasn't been set to the correct state.");
}

void Airplane::ascend(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Ascending", "Plane wasn't in correct state.");
    time += 1;
    if (engine == "jet" || time == 2) {
        height = height + 1000;
        output << callsign << " ascended to " << height << " ft." << std::endl;
        time = 0;
    }
    if(height == 5000) {
        status = "Leaving Airport";
    }
    ENSURE(this->getStatus() == "Leaving Airport" || this->getStatus() == "Ascending", "Plane hasn't been set to the correct state.");
}

void Airplane::leaveAirport(std::ostream &output, const std::string& airport) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Leaving Airport", "Plane wasn't in correct state.");
    output << callsign << " has left " << airport << std::endl;
    height = 10000;
    status = "Travelling";
    ENSURE(this->getStatus() == "Travelling", "Plane hasn't been set to the correct state.");
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

const std::string &Airplane::getSize() {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    return size;
}

void Airplane::setSize(const std::string &size) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    Airplane::size = size;
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
