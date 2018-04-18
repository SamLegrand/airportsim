//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_AIRPORT_H
#define AIRPORTSIM_AIRPORT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "runway.h"


class Airport {
    std::string name;
    std::string iata;
    std::string callsign;
    std::vector<Runway*> runways;
    std::vector<Airplane*> gates;
    int passengers;
public:
    void setName(const std::string &name);
    void setIata(const std::string &iata);
    void setCallsign(const std::string &callsign);
    void setGates(const unsigned int &gate);
    void setRunways(const std::vector<Runway *> &runways);
    void setPassengers(const int &passengers);
    const std::string &getName() const;
    const std::string &getIata() const;
    const std::string &getCallsign() const;
    const std::vector<Runway *> &getRunways() const;
    const std::vector<Airplane*> &getGatesVector() const;
    const int getGates() const;
    const int &getPassengers() const;
    void printInfo(std::ofstream &output) const;
    Runway* findRunway(std::string runwayName);

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    int getAvailableGate();

    /**
     * REQUIRE(gate > 0 && gate <= this->getGates(), "Gate should be a valid value.");
     * ENSURE(this->findPlaneInGate(airplane) == gate, "Plane wasn't added to correct gate.");
     */
    void addPlaneToGate(Airplane *airplane, int gate);

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * ENSURE(this->findPlaneInGate(airplane) == -1, "Plane wasn't correctly removed from gate.");
     */
    void removePlaneFromGate(Airplane *airplane);

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    int findPlaneInGate(Airplane *airplane);

    /**
     * REQUIRE(_runway->airplane == NULL, "Runway isn't properly initialised.");
     */
    void addRunway(Runway* _runway);

    /**
     * REQUIRE(runway > 0 && (unsigned)runway < this->getRunways().size(), "Runway should be a valid value.");
     */
    void addPlaneToRunway(Airplane* airplane, int runway);

    /**
     * REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
     * ENSURE(this->findPlaneInRunway(airplane) == NULL, "Plane wasn't correctly removed from runway.");
     */
    void removePlaneFromRunway(Airplane* airplane);

    /**
     * REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
     */
    Runway* getAvailableRunway();

    /**
     * REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
     */
    Runway* findPlaneInRunway(Airplane* airplane);
};


#endif //AIRPORTSIM_AIRPORT_H
