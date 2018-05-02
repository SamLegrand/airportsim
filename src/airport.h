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
    Airport* initCheck;
    std::string name;
    std::string iata;
    std::string callsign;
    std::vector<std::string> taxipoints;
    std::vector<Runway*> runways;
    std::vector<Airplane*> gates;
    Airplane* h3000;
    Airplane* h5000;
    int passengers;
public:
    Airport();
    bool properlyInitialized();
    void printInfo(std::ofstream &output) const;

    const std::string &getName() const;
    void setName(const std::string &name);

    const std::string &getIata() const;
    void setIata(const std::string &iata);

    const std::string &getCallsign() const;
    void setCallsign(const std::string &callsign);

    const std::vector<std::string> &getTaxipoints() const;
    void setTaxipoints(const std::vector<std::string> &taxipoints);

    const std::vector<Runway *> &getRunways() const;
    void setRunways(const std::vector<Runway *> &runways);

    const std::vector<Airplane*> &getGatesVector() const;
    const int getGates() const;
    void setGates(const unsigned int &gate);

    Airplane *getH3000() const;
    void setH3000(Airplane *h3000);

    Airplane *getH5000() const;
    void setH5000(Airplane *h5000);

    const int &getPassengers() const;
    void setPassengers(const int &passengers);


    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    Runway* findRunwayByRunwayName(std::string runwayName);

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    Runway* findRunwayByTaxiName(std::string taxipoint);

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    Runway* findNextRunwayToGate(Runway* runway);

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    Runway* findNextRunwayToRunway(Runway* runway);

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    Runway* findRunwayByTaxipointToGate(Airplane* airplane);

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    Runway* findRunwayByTaxipointToRunway(Airplane* airplane);

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    void sortRunways();

    /**
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     */
    Runway* getRunwayByAirplane(Airplane* airplane);

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

    /**
     * REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
     */
    Runway* findPlaneInCrossing(Airplane* airplane);

    /**
     * REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
     */
    Runway* findNearestAvailableRunway(Airplane* airplane);
};


#endif //AIRPORTSIM_AIRPORT_H
