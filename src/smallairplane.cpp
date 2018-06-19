//
// Created by sam on 16.05.18.
//

#include "smallairplane.h"

void SmallAirplane::unboardPlane(std::ostream &output, const std::string &airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Small plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Unboarding Plane", "Small plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers exited " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    if (time == 5) {
        status = "Checking Plane";
        time = 0;
    }
    ENSURE(this->getStatus() == "Checking Plane" || this->getStatus() == "Unboarding Plane", "Small plane should be set to the correct state.");
}

void SmallAirplane::checkPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Small plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Checking Plane", "Small plane has to the be in correct state.");
    output << callsign << " has been checked for technical malfunctions" << std::endl;
    status = "Refueling Plane";
    time = 0;
    ENSURE(this->getStatus() == "Refueling Plane" || this->getStatus() == "Checking Plane", "Small plane should be set to the correct state.");
}

void SmallAirplane::boardPlane(std::ostream &output, const std::string& airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Small plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Boarding Plane", "Small plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers boarded " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    if (time == 5) {
        status = "Standing at Gate";
        time = 0;
    }
    ENSURE(this->getStatus() == "Standing at Gate" || this->getStatus() == "Boarding Plane", "Small plane should be set to the correct state.");
}

void SmallAirplane::pushBack(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Small plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Pushing back", "Small plane has to the be in correct state.");
    output << callsign << " starting pushback" << std::endl;
    time = 0;
    status = "Taxiing to Runway";
    ENSURE(this->getStatus() == "Taxiing to Runway" || this->getStatus() == "Pushing back", "Small plane should be set to the correct state.");
}

void SmallAirplane::consumeFuel() {
    REQUIRE(this->properlyInitialized(), "Small plane wasn't properly initialized.");
    if (engine == "propeller"){
        fuel -= 10;
        return;
    }
    fuel -= 25;
}

void SmallAirplane::unboardAtRunway(std::ostream &output, const std::string &airport, const std::string &runway) {
    REQUIRE(this->properlyInitialized(), "Small plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Emergency Unboarding", "Small plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers exited " << callsign << " at runway " << runway << " of " << airport << " due to an emergency landing"<< std::endl;
    }
    if (time == 5) {
        status = "Emergency Checking";
        time = 0;
    }
    ENSURE(this->getStatus() == "Emergency Checking" || this->getStatus() == "Emergency Unboarding", "Small plane should be set to the correct state.");
}

void SmallAirplane::checkAtRunway(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Small plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Emergency Checking", "Small plane has to the be in correct state.");
    output << callsign << " has been checked for technical malfunctions" << std::endl;
    status = "Emergency Refueling";
    time = 0;
    ENSURE(this->getStatus() == "Emergency Refueling" || this->getStatus() == "Emergency Checking", "Small plane should be set to the correct state.");
}

void SmallAirplane::refuelAtRunway(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Small plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Emergency Refueling", "Small plane has to the be in correct state.");
    fuel += 10000;
    output << callsign << " has been refueled" << std::endl;
    status = "Landed";
    ENSURE(this->getStatus() == "Landed", "Small plane should be set to the correct state.");
}

void SmallAirplane::refuelPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Small plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Refueling Plane", "Small plane has to the be in correct state.");
    fuel += 10000;
    output << callsign << " has been refueled" << std::endl;
    status = "Boarding Plane";
    ENSURE(this->getStatus() == "Boarding Plane", "Small plane should be set to the correct state.");
}
