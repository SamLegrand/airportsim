//
// Created by sam on 16.05.18.
//

#include "smallairplane.h"

void SmallAirplane::unboardPlane(std::ostream &output, const std::string &airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Unboarding Plane", "Plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers exited " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    if (time == 5) {
        status = "Checking Plane";
        time = 0;
    }
    ENSURE(this->getStatus() == "Checking Plane" || this->getStatus() == "Unboarding Plane", "Plane should be set to the correct state.");
}

void SmallAirplane::checkPlane(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Checking Plane", "Plane has to the be in correct state.");
    output << callsign << " has been checked for technical malfunctions" << std::endl;
    status = "Refueling Plane";
    time = 0;
    ENSURE(this->getStatus() == "Refueling Plane" || this->getStatus() == "Checking Plane", "Plane should be set to the correct state.");
}

void SmallAirplane::boardPlane(std::ostream &output, const std::string& airport, int gate) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Boarding Plane", "Plane has to the be in correct state.");
    time += 1;
    if (time == 1) {
        output << passengers << " passengers boarded " << callsign << " at gate " << gate << " of " << airport << std::endl;
    }
    if (time == 5) {
        status = "Standing at Gate";
        time = 0;
    }
    ENSURE(this->getStatus() == "Standing at Gate" || this->getStatus() == "Boarding Plane", "Plane should be set to the correct state.");
}

void SmallAirplane::pushBack(std::ostream &output) {
    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
    REQUIRE(this->getStatus() == "Pushing back", "Plane has to the be in correct state.");
    output << callsign << " starting pushback" << std::endl;
    time = 0;
    status = "Taxiing to Runway";
    ENSURE(this->getStatus() == "Taxiing to Runway" || this->getStatus() == "Pushing back", "Plane should be set to the correct state.");
}

void SmallAirplane::consumeFuel() {
    if (engine == "propeller"){
        fuel -= 10;
        return;
    }
    fuel -= 25;
}
