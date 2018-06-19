//
// Created by sam on 01.03.18.
//

#include "airplane.h"
#include "Exporter.h"
#include "utils.h"

Airplane::Airplane(){
    time = 0;
    communicating = true;
    squawk = 0;
    initCheck = this;
    awaitingLeader = false;
    hasFlightPlan = false;
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

//void Airplane::refuelPlane(std::ostream &output) {
//    REQUIRE(this->properlyInitialized(), "Plane wasn't properly initialized.");
//    REQUIRE(this->getStatus() == "Refueling Plane", "Plane has to the be in correct state.");
//    output << callsign << " has been refueled" << std::endl;
//    status = "Boarding Plane";
//    ENSURE(this->getStatus() == "Boarding Plane", "Plane should be set to the correct state.");
//}

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
    awaitingLeader = true;
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
           Airplane::status == "Taxiing to Runway" ||
           Airplane::status == "Pushing Back";
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

void Airplane::executeTaxiingToGate(Runway *runway, Runway *nextrunway, Airport *airport, Exporter &exporter,
                                    std::ostream &SimOutput, unsigned int &simTime) {
    if (isCommunicating()) {
        if (!nextrunway) {
            if (getTime() == 1) {
                exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", taxi to gate " + to_string(airport->findPlaneInGate(this)) + " via " + runway->getTaxipoint() + ".");
                awaitingLeader = false;
                return;
            }
            exporter.printAirleaderMessage(simTime, getNumber(), "Taxi to gate " + to_string(airport->findPlaneInGate(this)) + " via " + runway->getTaxipoint() + ", " + getCallsign() + ".");
            setTime(0);
            setCommunication(false);
            return;
        }
        if (getTime() == 1) {
            exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", taxi to holding point " + nextrunway->getName() + " via " + runway->getTaxipoint() + ".");
            awaitingLeader = false;
            return;
        }
        exporter.printAirleaderMessage(simTime, getNumber(), "Taxi to holding point " + nextrunway->getName() + " via " + runway->getTaxipoint() + ", " + getCallsign() + ".");
        setTime(0);
        setCommunication(false);
        return;
    }
    if (getTime() == 5) {
        if (!nextrunway) {
            SimOutput << getCallsign() << " is taxiing to gate " << airport->findPlaneInGate(this) << " via " << runway->getTaxipoint() << std::endl;
            runway->setTaxipointToGate(NULL);
            setTime(0);
            setStatus("Unboarding Plane");
            setCommunication(true);
            return;
        }
        setStatus("Waiting to cross to Gate");
        setTime(0);
        setCommunication(true);
    }
}

void Airplane::executeWaitingToCrossToGate(Runway *runway, Runway *nextrunway, Airport *airport, Exporter &exporter,
                                           std::ostream &SimOutput, unsigned int &simTime) {
    if (getTime() == 1) {
        exporter.printAirleaderMessage(simTime, getNumber(), airport->getCallsign() + ", " + getCallsign() + ", holding short at " + runway->getName() + ".");
        awaitingLeader = true;
        return;
    }
    if (getTime() == 3) {
        runway = airport->findPlaneInCrossing(this);
        //SimOutput << airplane->getCallsign() << " is taxiing to runway " << nextrunway->getName() << " via " << runway->getTaxipoint() << std::endl;
        exporter.printAirleaderMessage(simTime, getNumber(), "Cleared to cross " + runway->getName() + " to holding point " + runway->getTaxipoint() + ".");
        setTime(0);
        setStatus("Crossing to Gate");
        awaitingLeader = true;
        return;
    }
    if (getTime() == 6) {
        exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", hold position.");
        awaitingLeader = false;
        return;
    }
    if (getTime() == 7) {
        exporter.printAirleaderMessage(simTime, getNumber(), "Holding position, " + getCallsign() + ".");
        awaitingLeader = true;
        return;
    }
    if (nextrunway->ableToCross() && !nextrunway->getTaxipointToGate()) {
        runway->setTaxipointToGate(NULL);
        nextrunway->setAirplaneCrossing(this);
        exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", cleared to cross " + nextrunway->getName() + ", to holding point " + nextrunway->getTaxipoint() + ".");
        setTime(2);
        awaitingLeader = false;
        return;
    }
    setTime(5);
}

void Airplane::executeTaxiingToRunway(Runway *runway, Airport *airport, Exporter &exporter, std::ostream &SimOutput,
                                      unsigned int &simTime) {
    if (isCommunicating()) {
        if (getTime() == 1) {
            exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", taxi to holding point " + runway->getName() + " via " + runway->getTaxipoint() + ".");
            awaitingLeader = false;
            return;
        }
        exporter.printAirleaderMessage(simTime, getNumber(), "Taxi to holding point " + runway->getName() + " via " + runway->getTaxipoint() + ", " + getCallsign() + ".");
        setTime(0);
        setCommunication(false);
        return;
    }
    if (getTime() == 5) {
        setStatus("Waiting to cross to Runway");
        setTime(0);
        setCommunication(true);
    }
}

void Airplane::executeWaitingToCrossToRunway(Runway *runway, Runway *nextrunway, Airport *airport, Exporter &exporter,
                                             std::ostream &SimOutput, unsigned int &simTime) {
    if (getTime() == 1) {
        exporter.printAirleaderMessage(simTime, getNumber(), airport->getCallsign() + ", " + getCallsign() + ", holding short at " + runway->getName() + ".");
        awaitingLeader = true;
        return;
    }
    if (getTime() == 3) {
        runway = airport->findPlaneInCrossing(this);
        nextrunway = airport->findNextRunwayToRunway(runway);
        //SimOutput << airplane->getCallsign() << " is taxiing to runway " << nextrunway->getName() << " via " << runway->getTaxipoint() << std::endl;
        exporter.printAirleaderMessage(simTime, getNumber(), "Cleared to cross " + runway->getName() + " to holding point " + nextrunway->getTaxipoint() + ".");
        setTime(0);
        setStatus("Crossing to Runway");
        awaitingLeader = true;
        return;
    }
    if (getTime() == 4) {
        runway = airport->findPlaneInRunway(this);
        exporter.printAirleaderMessage(simTime, getNumber(), "Lining up runway " + runway->getName() + " and wait, " + getCallsign() + ".");
        setTime(0);
        setStatus("Ready for Takeoff");
        return;
    }
    if (getTime() == 6) {
        exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", hold position.");
        awaitingLeader = false;
        return;
    }
    if (getTime() == 7) {
        exporter.printAirleaderMessage(simTime, getNumber(), "Holding position, " + getCallsign() + ".");
        awaitingLeader = true;
        return;
    }
    if (runway->getAirplane() == this) {
        runway->setTaxipointToRunway(NULL);
        exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", line-up runway " + runway->getName() + " and wait.");
        setTime(3);
        awaitingLeader = false;
        return;
    }
    if (runway->ableToCross() && !nextrunway->getTaxipointToRunway()) {
        runway->setTaxipointToRunway(NULL);
        runway->setAirplaneCrossing(this);
        exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", cleared to cross " + runway->getName() + ", to holding point " + nextrunway->getTaxipoint() + ".");
        setTime(2);
        awaitingLeader = false;
        return;
    }
    setTime(5);
}

void Airplane::executeFlyingWaitPattern(Airport *airport, Exporter &exporter, std::ostream &SimOutput,
                                        unsigned int &simTime) {
    if (getTime() == 1 && getHeight() == 10000 && airport->getH5000() == NULL) {
        airport->setH5000(this);
        exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", radar contact, descend and maintain five thousand feet, squawk " + to_string(getSquawk()) + ".");
        setTime(2);
        setStatus("Approaching");
        awaitingLeader = false;
        return;
    }
    if (getTime() == 1 && getHeight() == 5000 && airport->getH3000() == NULL) {
        airport->setH5000(NULL);
        airport->setH3000(this);
        exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", descend and maintain three thousand feet.");
        setStatus("Descending to 3k");
        setTime(0);
        awaitingLeader = false;
        return;
    }
    if (getTime() == 1 && getHeight() == 3000 && airport->getRunwayByAirplane(this)) {
        Runway* runway = airport->findNearestAvailableRunway(this);
        airport->setH3000(NULL);
        runway->setAirplane(this);
        setStatus("Final Approach");
        exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", cleared ILS approach runway " + runway->getName() + ".");
        setTime(0);
        awaitingLeader = false;
        return;
    }
    if (getTime() == 1) {
        exporter.printAirleaderMessage(simTime, airport->getIata(), getCallsign() + ", hold south on the one eighty radial, expect further clearance at " + "TODO");
        awaitingLeader = false;
        return;
    }
    flyWaitPattern(SimOutput);
    setTime(0);
    exporter.printAirleaderMessage(simTime, getNumber(), "Holding south on the one eighty radial, " + getCallsign() + ".");
    awaitingLeader = true;
}

void Airplane::landImmediately() {
    if (height > 0){
        height -= 500;
        return;
    }
    time = 0;
    status = "Emergency Unboarding";
}

bool Airplane::getSkipGateSteps() const {
    return skipGateSteps;
}

void Airplane::setSkipGateSteps(bool skipGateSteps) {
    Airplane::skipGateSteps = skipGateSteps;
}

int Airplane::getOriginalSquawk() const {
    return originalSquawk;
}

void Airplane::setOriginalSquawk(int originalSquawk) {
    Airplane::originalSquawk = originalSquawk;
}

bool Airplane::isAwaitingLeader() const {
    return awaitingLeader;
}

void Airplane::setAwaitingLeader(bool awaitingLeader) {
    Airplane::awaitingLeader = awaitingLeader;
}

bool Airplane::useFlightPlan() const {
    return hasFlightPlan;
}

void Airplane::setHasFlightPlan(bool hasFlightPlan) {
    Airplane::hasFlightPlan = hasFlightPlan;
}
