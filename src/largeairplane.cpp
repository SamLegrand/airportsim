//
// Created by sam on 16.05.18.
//

#include "largeairplane.h"

void LargeAirplane::unboardPlane(std::ostream &output, const std::string &airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Unboarding Plane", "Plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers exited " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    if (time == 15) {
        status = "Checking Plane";
        time = 0;
    }
    ENSURE(this->getStatus() == "Checking Plane" || this->getStatus() == "Unboarding Plane", "Plane should be set to the correct state.");
}

void LargeAirplane::checkPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Checking Plane", "Plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << callsign << " has been checked for technical malfunctions" << std::endl;
    }
    if (time == 3) {
        status = "Refueling Plane";
        time = 0;
    }
    ENSURE(this->getStatus() == "Refueling Plane" || this->getStatus() == "Checking Plane", "Plane should be set to the correct state.");
}

void LargeAirplane::boardPlane(std::ostream &output, const std::string& airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Boarding Plane", "Plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers boarded " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    if (time == 15) {
        status = "Standing at Gate";
        time = 0;
    }
    ENSURE(this->getStatus() == "Standing at Gate" || this->getStatus() == "Boarding Plane", "Plane should be set to the correct state.");
}

void LargeAirplane::pushBack(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Pushing back", "Plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << callsign << " starting pushback" << std::endl;
    }
    if (time == 3) {
        time = 0;
        status = "Taxiing to Runway";
    }
    ENSURE(this->getStatus() == "Taxiing to Runway" || this->getStatus() == "Pushing back", "Plane should be set to the correct state.");
}

void LargeAirplane::consumeFuel() {
    if (engine == "propeller"){
        fuel -= 100;
        return;
    }
    fuel -= 250;
}

void LargeAirplane::unboardAtRunway(std::ostream &output, const std::string &airport, const std::string &runway) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Emergency Unboarding", "Plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers exited " << callsign << " at runway " << runway << " of " << airport << " due to an emergency landing."<< std::endl;
    }
    if (time == 15) {
        status = "Emergency Checking";
        time = 0;
    }
    ENSURE(this->getStatus() == "Emergency Checking" || this->getStatus() == "Emergency Unboarding", "Plane should be set to the correct state.");
}

void LargeAirplane::checkAtRunway(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Emergency Checking", "Plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << callsign << " has been checked for technical malfunctions" << std::endl;
    }
    if (time == 3) {
        status = "Emergency Refueling";
        time = 0;
    }
    ENSURE(this->getStatus() == "Emergency Refueling" || this->getStatus() == "Emergency Checking", "Plane should be set to the correct state.");
}

void LargeAirplane::refuelAtRunway(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Emergency Refueling", "Plane has to the be in correct state.");
    if (time <= 1){
        fuel += 10000;
        time++;
    }
    if (time == 1){
        output << callsign << " has been refueled" << std::endl;
        status = "Landed";
        time = 0;
    }
    ENSURE(this->getStatus() == "Landed" || this->getStatus() == "Emergency Refueling", "Plane should be set to the correct state.");
}

void LargeAirplane::refuelPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Refueling Plane", "Plane has to the be in correct state.");
    if (time <= 1){
        fuel += 10000;
        time++;
    }
    if (time == 1){
        output << callsign << " has been refueled" << std::endl;
        status = "Boarding Plane";
        time = 0;
    }
    ENSURE(this->getStatus() == "Boarding Plane" || this->getStatus() == "Refueling Plane", "Plane should be set to the correct state.");
}
