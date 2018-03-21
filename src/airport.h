//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_AIRPORT_H
#define AIRPORTSIM_AIRPORT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "airplane.h"
#include "DesignByContract.h"

using namespace std;

class Airplane;

struct Runway {
    Runway(){
      Runway::name = "";
        Runway::airplane = NULL;
    };
    std::string name;
    Airplane* airplane;
};

class Airport {
    string name;
    string iata;
    string callsign;
    vector<Runway*> runways;
    vector<Airplane*> gates;
    int passengers;
public:
    void setName(const string &name);
    void setIata(const string &iata);
    void setCallsign(const string &callsign);
    void setGates(const unsigned int &gate);
    void setRunways(const vector<Runway *> &runways);
    void setPassengers(const int &passengers);
    const string &getName() const;
    const string &getIata() const;
    const string &getCallsign() const;
    const vector<Runway *> &getRunways() const;
    const int getGates() const;
    const int &getPassengers() const;
    void printInfo(ofstream &output) const;

    /**
     * REQUIRE(!gates.empty(), "There haven't been any gates added.");
     */
    int getAvailableGate();

    /**
     * REQUIRE(gate > 0 && gate <= this->gates.size(), "Gate should be a valid value.");
     * ENSURE(gates[gate - 1] == airplane, "Plane wasn't added to correct gate.");
     */
    void addPlaneToGate(Airplane *airplane, int gate);

    /**
     * REQUIRE(!gates.empty(), "There haven't been any gates added.");
     * ENSURE(gates[i] == NULL, "Plane wasn't correctly removed from gate.");
     */
    void removePlaneFromGate(Airplane *airplane);

    /**
     * REQUIRE(!gates.empty(), "There haven't been any gates added.");
     */
    int findPlaneInGate(Airplane *airplane);

    /**
     * REQUIRE(_runway->airplane == NULL, "Runway isn't properly initialised.");
     */
    void addRunway(Runway* _runway);

    /**
     * REQUIRE(runway > 0 && runway < this->runways.size(), "Runway should be a valid value.");
     */
    void addPlaneToRunway(Airplane* airplane, int runway);

    /**
     * REQUIRE(!runways.empty(), "There haven't been any runways added.");
     * ENSURE(runways[i] == NULL, "Plane wasn't correctly removed from runway.");
     */
    void removePlaneFromRunway(Airplane* airplane);

    /**
     * REQUIRE(!runways.empty(), "There haven't been any runways added.");
     */
    Runway* getAvailableRunway();

    /**
     * REQUIRE(!runways.empty(), "There haven't been any runways added.");
     */
    Runway* findPlaneInRunway(Airplane* airplane);
};


#endif //AIRPORTSIM_AIRPORT_H
