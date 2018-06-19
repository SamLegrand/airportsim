//
// Created by lena on 3/16/18.
//

#include <sstream>
#include "AirportSim.h"
#include "utils.h"
#include "Exporter.h"

AirportSim::AirportSim() {
    initCheck = this;
    airleaderoutput = "../AirControlOutput.txt";
    ENSURE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
}

AirportSim::AirportSim(const std::string &output){
    initCheck = this;
    airleaderoutput = output;
    ENSURE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
}

bool AirportSim::properlyInitialized() {
    return initCheck == this;
}

const std::vector<Airport *> &AirportSim::getAirports() {
    REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
    return airports;
}

void AirportSim::setAirports(const std::vector<Airport *> &airports) {
    REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
    AirportSim::airports = airports;
}

const std::vector<Airplane *> &AirportSim::getAirplanes() {
    REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
    return airplanes;
}

void AirportSim::setAirplanes(const std::vector<Airplane *> &airplanes) {
    REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
    AirportSim::airplanes = airplanes;
}

const std::string &AirportSim::getAirleaderoutput() const {
    return airleaderoutput;
}

void AirportSim::setAirleaderoutput(const std::string &airleaderoutput) {
    AirportSim::airleaderoutput = airleaderoutput;
}

void AirportSim::simulate(std::ostream& SimOutput) {
    REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
    unsigned int time = 720;
    Exporter exporter(airleaderoutput);
    Airport* airport = airports[0];
    Airplane* leaderplane = NULL;
    airport->sortRunways();
    int filecounter = -1;
    while (!checkSimEnd()) {
//        std::string min = "0" + to_string(time%60);
//        std::cout << time/60 << ":" << min.substr(min.size()-2) << std::endl;
        useGraphicsExporter(filecounter, exporter, false);

        for (unsigned int i = 0; i<airplanes.size(); ++i) {
            Airplane* airplane = airplanes[i];
            if (airplane->isAwaitingLeader()) {
                if (leaderplane == NULL) {
                    leaderplane = airplane;
                    continue;
                }
                if (leaderplane->getSquawk() < airplane->getSquawk()) {
                    leaderplane = airplane;
                    continue;
                }
                continue;
            }
            airplaneExcecute(airplane, airport, exporter, time, SimOutput);
        }

        if (leaderplane != NULL) {
            airplaneExcecute(leaderplane, airport, exporter, time, SimOutput);
            leaderplane = NULL;
        }

        time += 1;
    }
    exporter.closeAirleaderOutput();
}

bool AirportSim::checkSimEnd() {
    REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
    for (unsigned int i = 0; i<airplanes.size(); ++i) {
        Airplane* airplane = airplanes[i];
        if (airplane->getStatus() != "Travelling") {
            return false;
        }
    }
    return true;
}

void AirportSim::useGraphicsExporter(int &filecounter, Exporter &exporter, bool use){
    if (use){
        filecounter++;
        std::stringstream iniFileNameStream;
        std::stringstream fileNameStream;
        std::stringstream prevFileNameStream;
        iniFileNameStream << "../Engine/EngineTest" << filecounter << ".ini";
        fileNameStream << "EngineTest" << filecounter << ".ini";
        prevFileNameStream << "../Engine/EngineTest" << filecounter-1 << ".ini";
        std::string iniFileName = iniFileNameStream.str();
        std::string fileName = iniFileNameStream.str();
        std::string prevFileName = prevFileNameStream.str();
        std::ofstream myfile;
        myfile.open(iniFileName.c_str());
        exporter.exportIni(myfile, airports);
        if (!FileCompare(prevFileName, fileName)){
            exporter.generateImg(fileName.c_str());
        }
    }
}

bool AirportSim::handleEmergency(Airplane* airplane, Exporter &exporter, Airport* airport, const int &SimTime, std::ostream &output) {
    if (airplane->getStatus() == "Immediate Landing"){
        if (!airport->findPlaneInRunway(airplane)){
            Runway* runway = airport->findNearestAvailableRunway(airplane);
            if (runway){
                runway->setAirplane(airplane);
                exporter.printAirleaderMessage(SimTime, airport->getIata(), airport->getCallsign() + ", roger mayday, squawk seven seven zero zero, cleared ILS landing runway " + runway->getName() + ".");
                airplane->setAwaitingLeader(false);
            }
            return true;
        }
        airplane->landImmediately();
        return true;
    }
    if (airplane->getStatus() == "Emergency Unboarding"){
        airplane->unboardAtRunway(output, airport->getIata(), airport->findPlaneInRunway(airplane)->getName());
        return true;
    }
    if (airplane->getStatus() == "Emergency Checking"){
        airplane->checkAtRunway(output);
        return true;
    }
    if (airplane->getStatus() == "Emergency Refueling"){
        airplane->refuelAtRunway(output);
        airplane->setSkipGateSteps(true);
        airplane->setSquawk(airplane->getOriginalSquawk());
        return true;
    }
    if (airplane->getStatus() == "Emergency Landing"){
        if (airport->findPlaneInRunway(airplane)){
            airport->removePlaneFromRunway(airplane);
        }
        exporter.printAirleaderMessage(SimTime, airport->getIata(), airport->getCallsign() + ", roger mayday, squawk seven seven zero zero, emergency personal on standby, good luck!");
        airplane->setAwaitingLeader(false);
        airplane->setStatus("Travelling");
        return true;
    }
    if (airplane->getFuel() <= 0){
        airplane->setOriginalSquawk(airplane->getSquawk());
        airplane->setSquawk(7700);
        if (airplane->getHeight() >= 3000){
            exporter.printAirleaderMessage(SimTime, airplane->getNumber(), "Mayday mayday mayday, " + airport->getCallsign() + ", " + airplane->getCallsign() + ", out of fuel, request immediate landing, " + to_string(airplane->getPassengers()) + " persons on board.");
            airplane->setAwaitingLeader(true);
            airplane->setStatus("Immediate Landing");
        }
        else{
            exporter.printAirleaderMessage(SimTime, airplane->getNumber(), "Mayday mayday mayday, " + airport->getCallsign() + ", " + airplane->getCallsign() + ", out of fuel, performing emergency landing, " + to_string(airplane->getPassengers()) + " persons on board.");
            airplane->setAwaitingLeader(true);
            airplane->setStatus("Emergency Landing");
        }
        return true;
    }
    return false;
}

void AirportSim::airplaneExcecute(Airplane *airplane, Airport *airport, Exporter &exporter, unsigned int &time,
                                  std::ostream &SimOutput) {
    if (airplane->getStatus() == "Travelling") {
        return;
    }
    if (handleEmergency(airplane, exporter, airport, time, SimOutput)) return;
    if (airplane->getStatus() == "Leaving Airport") {
        airport->removePlaneFromRunway(airplane);
        airplane->leaveAirport(SimOutput, airport->getName());
        return;
    }
    if (airplane->getStatus() == "Ascending") {
        airplane->ascend(SimOutput);
        return;
    }
    if (airplane->getStatus() == "Taking Off") {
        if (airplane->getTime() != 0 || !airplane->useFlightPlan() || time%60 == (unsigned int)airplane->getDeparture()){
            Runway *runway = airport->findPlaneInRunway(airplane);
            airplane->takeOff(SimOutput, airport->getName(), runway->getName());
        }
        return;
    }
    if (airplane->getStatus() == "Ready for Takeoff"){
        airplane->setTime(airplane->getTime() + 1);
        Runway *runway = airport->findPlaneInRunway(airplane);
        if (airplane->getTime() == 1) {
            exporter.printAirleaderMessage(time, airport->getIata(), airplane->getCallsign() + ", runway "+ runway->getName() + " cleared for take-off.");
            airplane->setAwaitingLeader(false);
            return;
        }
        exporter.printAirleaderMessage(time, airplane->getNumber(), "Runway " + runway->getName() + " cleared for take-off, " + airplane->getCallsign() + ".");
        airplane->readyForTakeoff(SimOutput, airport->getName(), runway->getName());
        airplane->setTime(0);
        return;
    }
    if (airplane->getStatus() == "Crossing to Runway") {
        Runway* runway = airport->findPlaneInCrossing(airplane);
        Runway* nextrunway = airport->findNextRunwayToRunway(runway);
        SimOutput << airplane->getCallsign() << " is crossing " << runway->getName() << std::endl;
        runway->setAirplaneCrossing(NULL);
        nextrunway->setTaxipointToRunway(airplane);
        airplane->setStatus("Taxiing to Runway");
        return;
    }
    if (airplane->getStatus() == "Waiting to cross to Runway") {
        airplane->setTime(airplane->getTime() + 1);
        Runway *runway = airport->findRunwayByTaxipointToRunway(airplane);
        Runway *nextrunway = airport->findNextRunwayToRunway(runway);
        airplane->executeWaitingToCrossToRunway(runway, nextrunway, airport, exporter, SimOutput, time);
        return;
    }
    if (airplane->getStatus() == "Taxiing to Runway") {
        airplane->setTime(airplane->getTime() + 1);
        Runway *runway = airport->findRunwayByTaxipointToRunway(airplane);
        airplane->executeTaxiingToRunway(runway, airport, exporter, SimOutput, time);
        return;
    }
    if (airplane->getStatus() == "Pushing back") {
        if (airplane->isCommunicating()) {
            airplane->setTime(airplane->getTime() + 1);
            if (airplane->getTime() == 1) {
                exporter.printAirleaderMessage(time, airplane->getNumber(), airport->getCallsign() + ", " + airplane->getCallsign() + " at gate " + to_string(airport->findPlaneInGate(airplane)) + ", requesting pushback.");
                airplane->setAwaitingLeader(true);
                return;
            }
            if (airplane->getTime() == 2) {
                exporter.printAirleaderMessage(time, airport->getIata(), airplane->getCallsign() + ", " + airport->getCallsign() + ", pushback approved.");
                airplane->setAwaitingLeader(false);
                return;
            }
            exporter.printAirleaderMessage(time, airplane->getNumber(), "Pushback approved, " + airplane->getCallsign() + ".");
            airport->removePlaneFromGate(airplane);
            airplane->setCommunication(false);
            airplane->setTime(0);
            return;
        }
        airplane->pushBack(SimOutput);
        if (airplane->getStatus() == "Taxiing to Runway") {
            exporter.printAirleaderMessage(time, airplane->getNumber(), airplane->getCallsign() + ", ready to taxi.");
            airplane->setCommunication(true);
        }
        return;
    }
    if(airplane->getStatus() == "Standing at Gate") {
        airplane->setTime(airplane->getTime() + 1);
        Runway* dest = airport->getRunwayByAirplane(airplane);
        Runway* runway = airport->getRunways().back();
        if (airplane->getTime() == 1) {
            airplane->stand(SimOutput, airport->findPlaneInGate(airplane));
        }
        if (airplane->getTime() == 2) {
            dest = airport->findPlaneInRunway(airplane);
            exporter.printAirleaderMessage(time, airport->getIata(), airplane->getCallsign() + ", " + airport->getCallsign() + ", cleared to " + dest->getName() + ", maintain five thousand, expect flight level one zero zero - ten minutes after departure, squawk " + to_string(airplane->getSquawk()) + ".");
            airplane->setAwaitingLeader(false);
            return;
        }
        if (airplane->getTime() == 3) {
            dest = airport->findPlaneInRunway(airplane);
            exporter.printAirleaderMessage(time, airplane->getNumber(), "Cleared to " + dest->getName() + ", initial altitude five thousand, expecting one zero zero in ten, squawking " + to_string(airplane->getSquawk()) + ", " + airplane->getCallsign() + ".");
            airplane->setStatus("Pushing back");
            airplane->setCommunication(true);
            airplane->setTime(0);
            return;
        }
        if (dest && !runway->getTaxipointToRunway()) {
            dest->setAirplane(airplane);
            exporter.printAirleaderMessage(time, airplane->getNumber(), airport->getCallsign() + ", " + airplane->getCallsign() + ", requesting IFR clearancy to " + dest->getName() + ".");
            runway->setTaxipointToRunway(airplane);
            airplane->setTime(1);
            airplane->setAwaitingLeader(true);
            return;
        }
        airplane->setTime(5);
        return;
    }
    if (airplane->getStatus() == "Boarding Plane" || (airplane->getSkipGateSteps() && airplane->getStatus() == "Unboarding Plane")) {
        if (airplane->useFlightPlan() && airplane->getTime() == 0){
            if (!checkDepartureTime(airplane, airport, time)) return;
        }
        airplane->setStatus("Boarding Plane");
        airplane->boardPlane(SimOutput, airport->getName(), airport->findPlaneInGate(airplane));
        if (airplane->getSkipGateSteps()){
            airplane->setSkipGateSteps(false);
        }
        return;
    }
    if (airplane->getStatus() == "Refueling Plane") {
        airplane->refuelPlane(SimOutput);
        return;
    }
    if (airplane->getStatus() == "Checking Plane") {
        airplane->checkPlane(SimOutput);
        return;
    }
    if (airplane->getStatus() == "Unboarding Plane") {
        airplane->unboardPlane(SimOutput, airport->getName(), airport->findPlaneInGate(airplane));
        return;
    }
    if (airplane->getStatus() == "Crossing to Gate") {
        Runway* runway = airport->findPlaneInCrossing(airplane);
        SimOutput << airplane->getCallsign() << " is crossing " << runway->getName() << std::endl;
        runway->setAirplaneCrossing(NULL);
        runway->setTaxipointToGate(airplane);
        airplane->setStatus("Taxiing to Gate");
        airplane->setCommunication(true);
        return;
    }
    if (airplane->getStatus() == "Waiting to cross to Gate") {
        airplane->setTime(airplane->getTime() + 1);
        Runway *runway = airport->findRunwayByTaxipointToGate(airplane);
        Runway *nextrunway = airport->findNextRunwayToGate(runway);
        airplane->executeWaitingToCrossToGate(runway, nextrunway, airport, exporter, SimOutput, time);
        return;
    }
    if (airplane->getStatus() == "Taxiing to Gate") {
        airplane->setTime(airplane->getTime() + 1);
        Runway *runway = airport->findRunwayByTaxipointToGate(airplane);
        Runway *nextrunway = airport->findNextRunwayToGate(runway);
        airplane->executeTaxiingToGate(runway, nextrunway, airport, exporter, SimOutput, time);
        return;
    }
    if (airplane->getStatus() == "Landed") {
        Runway* runway = airport->findPlaneInRunway(airplane);
        airplane->landed(SimOutput, airport->getName(), runway->getName());
        int gate = airport->getAvailableGate();
        if (runway->getTaxipointToGate() == NULL && gate != -1) {
            exporter.printAirleaderMessage(time, airplane->getNumber(), airport->getCallsign() + ", " + airplane->getCallsign() + ", runway " + runway->getName() + " vacated.");
            airport->addPlaneToGate(airplane, gate);
            runway->setAirplane(NULL);
            runway->setTaxipointToGate(airplane);
            airplane->setStatus("Taxiing to Gate");
            airplane->setCommunication(true);
        }
        return;
    }
    if (airplane->getStatus() == "Landing") {
        Runway* runway = airport->findPlaneInRunway(airplane);
        airplane->land(SimOutput, airport->getName(), runway->getName());
        return;
    }
    if (airplane->getStatus() == "Final Approach") {
        Runway* runway = airport->findPlaneInRunway(airplane);
        if (airplane->isCommunicating()) {
            exporter.printAirleaderMessage(time, airplane->getNumber(), "Cleared ILS approach runway " + runway->getName() + ", " + airplane->getCallsign() + ".");
            airplane->setCommunication(false);
            return;
        }
        airplane->finalapproach(SimOutput, airport->getName(), runway->getName());
        return;
    }
    if (airplane->getStatus() == "Flying wait pattern") {
        airplane->executeFlyingWaitPattern(airport, exporter, SimOutput, time);
        return;
    }
    if (airplane->getStatus() == "Descending to 3k") {
        if (airplane->isCommunicating()) {
            exporter.printAirleaderMessage(time, airplane->getNumber(), "Descend and maintain three thousand feet, " + airplane->getCallsign() + ".");
            airplane->setCommunication(false);
            return;
        }
        airplane->descendTo3k(SimOutput);
        return;
    }
    if (airplane->getStatus() == "Descending to 5k") {
        airplane->descendTo5k(SimOutput);
        return;
    }
    if (airplane->getStatus() == "Approaching") {
        airplane->setTime(airplane->getTime() + 1);
        if (airplane->getTime() == 1) {
            airplane->setHeight(10000);
            exporter.printAirleaderMessage(time, airplane->getNumber(), airport->getCallsign()+ ", " + airplane->getCallsign() + ", arriving at " + airport->getName() + ".");
            airplane->setAwaitingLeader(true);
            return;
        }
        if (airport->getH5000() == NULL || airport->getH5000() == airplane) {
            if (airplane->getTime() == 2) {
                airport->setH5000(airplane);
                exporter.printAirleaderMessage(time, airport->getIata(), airplane->getCallsign() + ", radar contact, descend and maintain five thousand feet, squawk " + to_string(airplane->getSquawk()) + ".");
                airplane->setAwaitingLeader(false);
                return;
            }
            if (airplane->getTime() == 3) {
                exporter.printAirleaderMessage(time, airplane->getNumber(), "Descend and maintain five thousand feet, squawking " + to_string(airplane->getSquawk()) + ", " + airplane->getCallsign() + ".");
                airplane->approach(SimOutput, airport->getName());
                airplane->setTime(0);
                return;
            }
        }
        airplane->setTime(1);
        exporter.printAirleaderMessage(time, airport->getIata(), airplane->getCallsign() + ", hold south on the one eighty radial, expect further clearance at " + "TODO");
        airplane->setStatus("Flying wait pattern");
        airplane->setAwaitingLeader(false);
        return;
    }
}

int AirportSim::getNumberOfAirplanesInGate(std::vector<Airplane*> &airplanes){
    int counter = 0;
    for (unsigned int i = 0; i < airplanes.size(); ++i) {
        Airplane* airplane = airplanes[i];
        if (airplane->isAtGate()){
            counter++;
        }
    }
    return counter;
}

bool AirportSim::checkDepartureTime(Airplane* airplane, Airport* airport, const int &SimTime){
    if (airport->getRunwayByAirplane(airplane)){
        int runwayIndex = airport->getRunwayIndex(airport->getRunwayByAirplane(airplane));
        int nrTaxipoints = runwayIndex;
        int nrCrossings = runwayIndex - 1;
        int totalTime = 0;
        if (dynamic_cast<SmallAirplane*>(airplane)){
            totalTime += 5;
            totalTime += 1;
        }
        if (dynamic_cast<MediumAirplane*>(airplane)){
            totalTime += 10;
            totalTime += 2;
        }
        if (dynamic_cast<LargeAirplane*>(airplane)){
            totalTime += 15;
            totalTime += 3;
        }
        totalTime += (2*getNumberOfAirplanesInGate(airplanes)) + (getNumberOfAirplanesInGate(airplanes) + 4) + (nrCrossings) + (5*nrTaxipoints) + 2 + 15;
        if ((SimTime + totalTime)%60 == airplane->getDeparture()){
            return true;
        }
    }
    return false;
}
