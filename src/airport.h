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
#include "smallairplane.h"
#include "mediumairplane.h"
#include "largeairplane.h"

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
    /**
     * ENSURE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     */
    Airport();
    /**
     *
     * @return
     */
    bool properlyInitialized();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param output
     */
    void printInfo(std::ofstream &output);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    const std::string &getName();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param name
     */
    void setName(const std::string &name);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    const std::string &getIata();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param iata
     */
    void setIata(const std::string &iata);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    const std::string &getCallsign();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param callsign
     */
    void setCallsign(const std::string &callsign);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    const std::vector<std::string> &getTaxipoints();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param taxipoints
     */
    void setTaxipoints(const std::vector<std::string> &taxipoints);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    const std::vector<Runway *> &getRunways();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param runways
     */
    void setRunways(const std::vector<Runway *> &runways);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    const std::vector<Airplane*> &getGatesVector();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    const int getGates();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param gate
     */
    void setGates(const unsigned int &gate);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    Airplane *getH3000();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param h3000
     */
    void setH3000(Airplane *h3000);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    Airplane *getH5000();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param h5000
     */
    void setH5000(Airplane *h5000);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @return
     */
    const int &getPassengers();
    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * @param passengers
     */
    void setPassengers(const int &passengers);


    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * @param runwayName
     * @return
     */
    Runway* findRunwayByRunwayName(std::string runwayName);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * @param taxipoint
     * @return
     */
    Runway* findRunwayByTaxiName(std::string taxipoint);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * @param runway
     * @return
     */
    Runway* findNextRunwayToGate(Runway* runway);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * @param runway
     * @return
     */
    Runway* findNextRunwayToRunway(Runway* runway);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * @param airplane
     * @return
     */
    Runway* findRunwayByTaxipointToGate(Airplane* airplane);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * @param airplane
     * @return
     */
    Runway* findRunwayByTaxipointToRunway(Airplane* airplane);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     */
    void sortRunways();

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * @param airplane
     * @return
     */
    Runway* getRunwayByAirplane(Airplane* airplane);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * @return
     */
    int getAvailableGate();

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(gate > 0 && gate <= this->getGates(), "Gate should be a valid value.");
     * ENSURE(this->findPlaneInGate(airplane) == gate, "Plane wasn't added to correct gate.");
     * @param airplane
     * @param gate
     */
    void addPlaneToGate(Airplane *airplane, int gate);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * ENSURE(this->findPlaneInGate(airplane) == -1, "Plane wasn't correctly removed from gate.");
     * @param airplane
     */
    void removePlaneFromGate(Airplane *airplane);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(this->getGates() != 0, "There haven't been any gates added.");
     * @param airplane
     * @return
     */
    int findPlaneInGate(Airplane *airplane);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(_runway->airplane == NULL, "Runway isn't properly initialised.");
     * @param _runway
     */
    void addRunway(Runway* _runway);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
     * ENSURE(this->findPlaneInRunway(airplane) == NULL, "Plane wasn't correctly removed from runway.");
     * @param airplane
     */
    void removePlaneFromRunway(Airplane* airplane);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
     * @param airplane
     * @return
     */
    Runway* findPlaneInRunway(Airplane* airplane);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
     * @param airplane
     * @return
     */
    Runway* findPlaneInCrossing(Airplane* airplane);

    /**
     * REQUIRE(this->properlyInitialized(), "Airport wasn't properly initialized.");
     * REQUIRE(!this->getRunways().empty(), "There haven't been any runways added.");
     * @param airplane
     * @return
     */
    Runway* findNearestAvailableRunway(Airplane* airplane);

    int getRunwayIndex(Runway* runway);
};


#endif //AIRPORTSIM_AIRPORT_H
