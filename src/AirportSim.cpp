//
// Created by lena on 3/16/18.
//

#include <sstream>
#include "AirportSim.h"
#include "utils.h"
#include "Exporter.h"

AirportSim::AirportSim() {
    initCheck = this;
}

bool AirportSim::properlyInitialized() {
    return initCheck == this;
}

const std::vector<Airport *> &AirportSim::getAirports() const {
    return airports;
}

void AirportSim::setAirports(const std::vector<Airport *> &airports) {
    AirportSim::airports = airports;
}

const std::vector<Airplane *> &AirportSim::getAirplanes() const {
    return airplanes;
}

void AirportSim::setAirplanes(const std::vector<Airplane *> &airplanes) {
    AirportSim::airplanes = airplanes;
}

void AirportSim::simulate(std::ostream& SimOutput) {
    unsigned int time = 720;
    Exporter exporter;
    Airport* airport = airports[0];
    airport->sortRunways();
//    int filecounter = -1;
    while (!checkSimEnd()) {
//        std::string min = "0" + to_string(time%60);
//        std::cout << time/60 << ":" << min.substr(min.size()-2) << std::endl;
        // Graphics implementation
//        filecounter++;
//        std::stringstream iniFileNameStream;
//        std::stringstream fileNameStream;
//        std::stringstream prevFileNameStream;
//        iniFileNameStream << "../Engine/EngineTest" << filecounter << ".ini";
//        fileNameStream << "EngineTest" << filecounter << ".ini";
//        prevFileNameStream << "../Engine/EngineTest" << filecounter-1 << ".ini";
//        std::string iniFileName = iniFileNameStream.str();
//        std::string fileName = iniFileNameStream.str();
//        std::string prevFileName = prevFileNameStream.str();
//        std::ofstream myfile;
//        myfile.open(iniFileName.c_str());
//        exporter.exportIni(myfile, airports);
//        if (!FileCompare(prevFileName, fileName)){
//            exporter.generateImg(fileName.c_str());
//        }


        for (unsigned int i = 0; i<airplanes.size(); ++i) {
            Airplane* airplane = airplanes[i];
            if (airplane->getStatus() == "Travelling") {
                continue;
            }
            if (airplane->getStatus() == "Leaving Airport") {
                airport->removePlaneFromRunway(airplane);
                airplane->leaveAirport(SimOutput, airport->getName());
                continue;
            }
            if (airplane->getStatus() == "Ascending") {
                airplane->ascend(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Taking Off") {
                Runway *runway = airport->findPlaneInRunway(airplane);
//                if (runway == NULL) {
//                    continue;
//                }
                airplane->takeOff(SimOutput, airport->getName(), runway->getName());
                continue;
            }
            if (airplane->getStatus() == "Ready for Takeoff"){
                airplane->setTime(airplane->getTime() + 1);
                Runway *runway = airport->findPlaneInRunway(airplane);
                if (airplane->getTime() == 1) {
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", runway "+ runway->getName() + " cleared for take-off.");
                    continue;
                }
                exporter.printAirleaderMessage(time, "AIR", "Runway " + runway->getName() + " cleared for take-off, " + airplane->getCallsign() + ".");
                airplane->readyForTakeoff(SimOutput, airport->getName(), runway->getName());
                airplane->setTime(0);
                continue;
            }

            if (airplane->getStatus() == "Crossing to Runway") {
                Runway* runway = airport->findPlaneInCrossing(airplane);
                Runway* nextrunway = airport->findNextRunwayToRunway(runway);
                SimOutput << airplane->getCallsign() << " is crossing " << runway->getName() << std::endl;
                runway->setAirplaneCrossing(NULL);
                nextrunway->setTaxipointToRunway(airplane);
                airplane->setStatus("Taxiing to Runway");
                continue;
            }
            if (airplane->getStatus() == "Waiting to cross to Runway") {
                airplane->setTime(airplane->getTime() + 1);
                Runway *runway = airport->findRunwayByTaxipointToRunway(airplane);
                Runway *nextrunway = airport->findNextRunwayToRunway(runway);
                if (airplane->getTime() == 1) {
                    exporter.printAirleaderMessage(time, "AIR", airport->getCallsign() + ", " + airplane->getCallsign() + ", holding short at " + runway->getName() + ".");
                    continue;
                }
                if (airplane->getTime() == 3) {
                    runway = airport->findPlaneInCrossing(airplane);
                    nextrunway = airport->findNextRunwayToRunway(runway);
                    //SimOutput << airplane->getCallsign() << " is taxiing to runway " << nextrunway->getName() << " via " << runway->getTaxipoint() << std::endl;
                    exporter.printAirleaderMessage(time, "AIR", "Cleared to cross " + runway->getName() + " to holding point " + nextrunway->getTaxipoint() + ".");
                    airplane->setTime(0);
                    airplane->setStatus("Crossing to Runway");
                    continue;
                }
                if (airplane->getTime() == 4) {
                    runway = airport->findPlaneInRunway(airplane);
                    exporter.printAirleaderMessage(time, "AIR", "Lining up runway " + runway->getName() + " and wait, " + airplane->getCallsign() + ".");
                    airplane->setTime(0);
                    airplane->setStatus("Ready for Takeoff");
                    continue;
                }
                if (airplane->getTime() == 6) {
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", hold position.");
                    continue;
                }
                if (airplane->getTime() == 7) {
                    exporter.printAirleaderMessage(time, "AIR", "Holding position, " + airplane->getCallsign() + ".");
                    continue;
                }
                if (runway->getAirplane() == airplane) {
                    runway->setTaxipointToRunway(NULL);
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", line-up runway " + runway->getName() + " and wait.");
                    airplane->setTime(3);
                    continue;
                }
                if (runway->ableToCross() && !nextrunway->getTaxipointToRunway()) {
                    runway->setTaxipointToRunway(NULL);
                    runway->setAirplaneCrossing(airplane);
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", cleared to cross " + runway->getName() + ", to holding point " + nextrunway->getTaxipoint() + ".");
                    airplane->setTime(2);
                    continue;
                }
                airplane->setTime(5);
                continue;
            }
            if (airplane->getStatus() == "Taxiing to Runway") {
                airplane->setTime(airplane->getTime() + 1);
                Runway *runway = airport->findRunwayByTaxipointToRunway(airplane);
                if (airplane->isCommunicating()) {
                    if (airplane->getTime() == 1) {
                        exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", taxi to holding point " + runway->getName() + " via " + runway->getTaxipoint() + ".");
                        continue;
                    }
                    exporter.printAirleaderMessage(time, "AIR", "Taxi to holding point " + runway->getName() + " via " + runway->getTaxipoint() + ", " + airplane->getCallsign() + ".");
                    airplane->setTime(0);
                    airplane->setCommunication(false);
                    continue;
                }
                if (airplane->getTime() == 5) {
                    airplane->setStatus("Waiting to cross to Runway");
                    airplane->setTime(0);
                    airplane->setCommunication(true);
                }
                continue;
            }
            if (airplane->getStatus() == "Pushing back") {
                if (airplane->isCommunicating()) {
                    airplane->setTime(airplane->getTime() + 1);
                    if (airplane->getTime() == 1) {
                        exporter.printAirleaderMessage(time, "AIR", airport->getCallsign() + ", " + airplane->getCallsign() + " at gate " + to_string(airport->findPlaneInGate(airplane)) + ", requesting pushback.");
                        continue;
                    }
                    if (airplane->getTime() == 2) {
                        exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", " + airport->getCallsign() + ", pushback approved.");
                        continue;
                    }
                    exporter.printAirleaderMessage(time, "AIR", "Pushback approved, " + airplane->getCallsign() + ".");
                    airport->removePlaneFromGate(airplane);
                    airplane->setCommunication(false);
                    airplane->setTime(0);
                    continue;
                }
                airplane->pushBack(SimOutput);
                if (airplane->getStatus() == "Taxiing to Runway") {
                    exporter.printAirleaderMessage(time, "AIR", airplane->getCallsign() + ", ready to taxi.");
                    airplane->setCommunication(true);
                }
                continue;
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
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", " + airport->getCallsign() + ", cleared to " + dest->getName() + ", maintain five thousand, expect flight level one zero zero - ten minutes after departure, squawk " + to_string(airplane->getSquawk()) + ".");
                    continue;
                }
                if (airplane->getTime() == 3) {
                    dest = airport->findPlaneInRunway(airplane);
                    exporter.printAirleaderMessage(time, "AIR", "Cleared to " + dest->getName() + ", initial altitude five thousand, expecting one zero zero in ten, squawking " + to_string(airplane->getSquawk()) + ", " + airplane->getCallsign() + ".");
                    airplane->setStatus("Pushing back");
                    airplane->setCommunication(true);
                    airplane->setTime(0);
                    continue;
                }
                if (dest && !runway->getTaxipointToRunway()) {
                    dest->setAirplane(airplane);
                    exporter.printAirleaderMessage(time, "AIR", airport->getCallsign() + ", " + airplane->getCallsign() + ", requesting IFR clearancy to " + dest->getName() + ".");
                    runway->setTaxipointToRunway(airplane);
                    airplane->setTime(1);
                    continue;
                }
                airplane->setTime(5);
                continue;
            }
            if (airplane->getStatus() == "Boarding Plane") {
                airplane->boardPlane(SimOutput, airport->getName(), airport->findPlaneInGate(airplane));
                continue;
            }
            if (airplane->getStatus() == "Refueling Plane") {
                airplane->refuelPlane(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Checking Plane") {
                airplane->checkPlane(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Unboarding Plane") {
                airplane->unboardPlane(SimOutput, airport->getName(), airport->findPlaneInGate(airplane));
                continue;
            }
            if (airplane->getStatus() == "Crossing to Gate") {
                Runway* runway = airport->findPlaneInCrossing(airplane);
                SimOutput << airplane->getCallsign() << " is crossing " << runway->getName() << std::endl;
                runway->setAirplaneCrossing(NULL);
                runway->setTaxipointToGate(airplane);
                airplane->setStatus("Taxiing to Gate");
                airplane->setCommunication(true);
                continue;
            }
            if (airplane->getStatus() == "Waiting to cross to Gate") {
                airplane->setTime(airplane->getTime() + 1);
                Runway *runway = airport->findRunwayByTaxipointToGate(airplane);
                Runway *nextrunway = airport->findNextRunwayToGate(runway);
                if (airplane->getTime() == 1) {
                    exporter.printAirleaderMessage(time, "AIR", airport->getCallsign() + ", " + airplane->getCallsign() + ", holding short at " + runway->getName() + ".");
                    continue;
                }
                if (airplane->getTime() == 3) {
                    runway = airport->findPlaneInCrossing(airplane);
                    //SimOutput << airplane->getCallsign() << " is taxiing to runway " << nextrunway->getName() << " via " << runway->getTaxipoint() << std::endl;
                    exporter.printAirleaderMessage(time, "AIR", "Cleared to cross " + runway->getName() + " to holding point " + runway->getTaxipoint() + ".");
                    airplane->setTime(0);
                    airplane->setStatus("Crossing to Gate");
                    continue;
                }
                if (airplane->getTime() == 6) {
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", hold position.");
                    continue;
                }
                if (airplane->getTime() == 7) {
                    exporter.printAirleaderMessage(time, "AIR", "Holding position, " + airplane->getCallsign() + ".");
                    continue;
                }
                if (nextrunway->ableToCross() && nextrunway->getTaxipointToGate() == NULL) {
                    runway->setTaxipointToGate(NULL);
                    nextrunway->setAirplaneCrossing(airplane);
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", cleared to cross " + nextrunway->getName() + ", to holding point " + nextrunway->getTaxipoint() + ".");
                    airplane->setTime(2);
                    continue;
                }
                airplane->setTime(5);
                continue;
            }
            if (airplane->getStatus() == "Taxiing to Gate") {
                airplane->setTime(airplane->getTime() + 1);
                Runway *runway = airport->findRunwayByTaxipointToGate(airplane);
                Runway *nextrunway = airport->findNextRunwayToGate(runway);
                if (airplane->isCommunicating()) {
                    if (!nextrunway) {
                        if (airplane->getTime() == 1) {
                            exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", taxi to gate " + to_string(airport->findPlaneInGate(airplane)) + " via " + runway->getTaxipoint() + ".");
                            continue;
                        }
                        exporter.printAirleaderMessage(time, "AIR", "Taxi to gate " + to_string(airport->findPlaneInGate(airplane)) + " via " + runway->getTaxipoint() + ", " + airplane->getCallsign() + ".");
                        airplane->setTime(0);
                        airplane->setCommunication(false);
                        continue;
                    }
                    if (airplane->getTime() == 1) {
                        exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", taxi to holding point " + nextrunway->getName() + " via " + runway->getTaxipoint() + ".");
                        continue;
                    }
                    exporter.printAirleaderMessage(time, "AIR", "Taxi to holding point " + nextrunway->getName() + " via " + runway->getTaxipoint() + ", " + airplane->getCallsign() + ".");
                    airplane->setTime(0);
                    airplane->setCommunication(false);
                    continue;
                }
                if (airplane->getTime() == 5) {
                    if (!nextrunway) {
                        SimOutput << airplane->getCallsign() << " is taxiing to gate " << airport->findPlaneInGate(airplane) << " via " << runway->getTaxipoint() << std::endl;
                        runway->setTaxipointToGate(NULL);
                        airplane->setTime(0);
                        airplane->setStatus("Unboarding Plane");
                        airplane->setCommunication(true);
                        continue;
                    }
                    airplane->setStatus("Waiting to cross to Gate");
                    airplane->setTime(0);
                    airplane->setCommunication(true);
                }
                continue;
            }
            if (airplane->getStatus() == "Landed") {
                Runway* runway = airport->findPlaneInRunway(airplane);
                airplane->landed(SimOutput, airport->getName(), runway->getName());
                int gate = airport->getAvailableGate();
                if (runway->getTaxipointToGate() == NULL && gate != -1) {
                    exporter.printAirleaderMessage(time, "AIR", airport->getCallsign() + ", " + airplane->getCallsign() + ", runway " + runway->getName() + " vacated.");
                    airport->addPlaneToGate(airplane, gate);
                    runway->setAirplane(NULL);
                    runway->setTaxipointToGate(airplane);
                    airplane->setStatus("Taxiing to Gate");
                    airplane->setCommunication(true);
                }
                continue;
            }
            if (airplane->getStatus() == "Landing") {
                Runway* runway = airport->findPlaneInRunway(airplane);
                airplane->land(SimOutput, airport->getName(), runway->getName());
                continue;
            }
            if (airplane->getStatus() == "Final Approach") {
                Runway* runway = airport->findPlaneInRunway(airplane);
                if (airplane->isCommunicating()) {
                    exporter.printAirleaderMessage(time, "AIR", "Cleared ILS approach runway " + runway->getName() + ", " + airplane->getCallsign() + ".");
                    airplane->setCommunication(false);
                    continue;
                }
                airplane->finalapproach(SimOutput, airport->getName(), runway->getName());
                continue;
            }
            if (airplane->getStatus() == "Flying wait pattern") {
                airplane->setCommunication(true);
                airplane->setTime(airplane->getTime() + 1);
                if (airplane->getTime() == 1 && airplane->getHeight() == 10000 && airport->getH5000() == NULL) {
                    airport->setH5000(airplane);
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", radar contact, descend and maintain five thousand feet, squawk " + to_string(airplane->getSquawk()) + ".");
                    airplane->setTime(2);
                    airplane->setStatus("Approaching");
                    continue;
                }
                if (airplane->getTime() == 1 && airplane->getHeight() == 5000 && airport->getH3000() == NULL) {
                    airport->setH5000(NULL);
                    airport->setH3000(airplane);
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", descend and maintain three thousand feet.");
                    airplane->setStatus("Descending to 3k");
                    airplane->setTime(0);
                    continue;
                }
                if (airplane->getTime() == 1 && airplane->getHeight() == 3000 && airport->getRunwayByAirplane(airplane)) {
                    Runway* runway = airport->findNearestAvailableRunway(airplane);
                    airport->setH3000(NULL);
                    runway->setAirplane(airplane);
                    airplane->setStatus("Final Approach");
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", cleared ILS approach runway " + runway->getName() + ".");
                    airplane->setTime(0);
                    continue;
                }
                if (airplane->getTime() == 1) {
                    exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", hold south on the one eighty radial, expect further clearance at " + "TODO");
                    continue;
                }
                airplane->flyWaitPattern(SimOutput);
                airplane->setTime(0);
                exporter.printAirleaderMessage(time, "AIR", "Holding south on the one eighty radial, " + airplane->getCallsign() + ".");
                continue;
            }
            if (airplane->getStatus() == "Descending to 3k") {
                if (airplane->isCommunicating()) {
                    exporter.printAirleaderMessage(time, "AIR", "Descend and maintain three thousand feet, " + airplane->getCallsign() + ".");
                    airplane->setCommunication(false);
                    continue;
                }
                airplane->descendTo3k(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Descending to 5k") {
                airplane->descendTo5k(SimOutput);
                continue;
            }
            if (airplane->getStatus() == "Approaching") {
                airplane->setTime(airplane->getTime() + 1);
                if (airplane->getTime() == 1) {
                    airplane->setHeight(10000);
                    exporter.printAirleaderMessage(time, "AIR", airport->getCallsign()+ ", " + airplane->getCallsign() + ", arriving at " + airport->getName() + ".");
                    continue;
                }
                if (airport->getH5000() == NULL || airport->getH5000() == airplane) {
                    if (airplane->getTime() == 2) {
                        airport->setH5000(airplane);
                        exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", radar contact, descend and maintain five thousand feet, squawk " + to_string(airplane->getSquawk()) + ".");
                        continue;
                    }
                    if (airplane->getTime() == 3) {
                        exporter.printAirleaderMessage(time, "AIR", "Descend and maintain five thousand feet, squawking " + to_string(airplane->getSquawk()) + ", " + airplane->getCallsign() + ".");
                        airplane->approach(SimOutput, airport->getName());
                        airplane->setTime(0);
                        continue;
                    }
                }
                airplane->setTime(1);
                exporter.printAirleaderMessage(time, "ATC", airplane->getCallsign() + ", hold south on the one eighty radial, expect further clearance at " + "TODO");
                airplane->setStatus("Flying wait pattern");
                continue;
            }
        }
        time += 1;
    }
    exporter.closeAirleaderOutput();
}

bool AirportSim::checkSimEnd() {
    for (unsigned int i = 0; i<airplanes.size(); ++i) {
        Airplane* airplane = airplanes[i];
        if (airplane->getStatus() != "Travelling") {
            return false;
        }
    }
    return true;
}
