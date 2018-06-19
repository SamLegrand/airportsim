//
// Created by sam on 16.05.18.
//

#include "mediumairplane.h"

void MediumAirplane::unboardPlane(std::ostream &output, const std::string &airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Unboarding Plane", "Medium plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers exited " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    if (time == 10) {
        status = "Checking Plane";
        time = 0;
    }
    ENSURE(this->getStatus() == "Checking Plane" || this->getStatus() == "Unboarding Plane", "Medium plane should be set to the correct state.");
}

void MediumAirplane::checkPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Checking Plane", "Medium plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << callsign << " has been checked for technical malfunctions" << std::endl;
    }
    if (time == 2) {
        status = "Refueling Plane";
        time = 0;
    }
    ENSURE(this->getStatus() == "Refueling Plane" || this->getStatus() == "Checking Plane", "Medium plane should be set to the correct state.");
}

void MediumAirplane::boardPlane(std::ostream &output, const std::string& airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Boarding Plane", "Medium plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers boarded " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    if (time == 10) {
        status = "Standing at Gate";
        time = 0;
    }
    ENSURE(this->getStatus() == "Standing at Gate" || this->getStatus() == "Boarding Plane", "Medium plane should be set to the correct state.");
}

void MediumAirplane::pushBack(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Pushing back", "Medium plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << callsign << " starting pushback" << std::endl;
    }
    if (time == 2) {
        time = 0;
        status = "Taxiing to Runway";
    }
    ENSURE(this->getStatus() == "Taxiing to Runway" || this->getStatus() == "Pushing back", "Medium plane should be set to the correct state.");
}

void MediumAirplane::consumeFuel() {
    REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    if (engine == "propeller"){
        fuel -= 50;
        return;
    }
    fuel -= 175;
}

void MediumAirplane::unboardAtRunway(std::ostream &output, const std::string &airport, const std::string &runway) {
    REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Emergency Unboarding", "Medium plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers exited " << callsign << " at runway " << runway << " of " << airport << " due to an emergency landing."<< std::endl;
    }
    if (time == 10) {
        status = "Emergency Checking";
        time = 0;
    }
    ENSURE(this->getStatus() == "Emergency Checking" || this->getStatus() == "Emergency Unboarding", "Medium plane should be set to the correct state.");
}

void MediumAirplane::checkAtRunway(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Emergency Checking", "Medium plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << callsign << " has been checked for technical malfunctions" << std::endl;
    }
    if (time == 2) {
        status = "Emergency Refueling";
        time = 0;
    }
    ENSURE(this->getStatus() == "Emergency Refueling" || this->getStatus() == "Emergency Checking", "Medium plane should be set to the correct state.");
}

void MediumAirplane::refuelAtRunway(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Emergency Refueling", "Medium plane has to the be in correct state.");
    if (engine == "propeller"){
        fuel += 10000;
        output << callsign << " has been refueled" << std::endl;
        status = "Landed";
    }
    else{
        if (time <= 1){
            fuel += 10000;
        }
        if (time == 1){
            output << callsign << " has been refueled" << std::endl;
            status = "Landed";
        }
        time++;
    }
    ENSURE(this->getStatus() == "Landed" || this->getStatus() == "Emergency Refueling", "Medium plane should be set to the correct state.");
}

void MediumAirplane::refuelPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Refueling Plane", "Medium plane has to the be in correct state.");
    if (engine == "propeller"){
        fuel += 10000;
        output << callsign << " has been refueled" << std::endl;
        status = "Boarding Plane";
    }
    else{
        if (time <= 1){
            fuel += 10000;
            time++;
        }
        if (time == 1){
            output << callsign << " has been refueled" << std::endl;
            status = "Boarding Plane";
            time = 0;
        }
    }
    ENSURE(this->getStatus() == "Boarding Plane" || this->getStatus() == "Refueling Plane", "Medium plane should be set to the correct state.");
}
