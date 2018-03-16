//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_AIRPORT_H
#define AIRPORTSIM_AIRPORT_H

#include <iostream>
#include "runway.h"
#include <vector>
#include <fstream>
#include "airplane.h"
#include "DesignByContract.h"

using namespace std;

class Airplane;

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
    void setPassengers(const int &passengers);
    int getAvailableGate();
    const string &getName() const;
    const string &getIata() const;
    const string &getCallsign() const;
    const vector<Runway *> &getRunways() const;
    const vector<Airplane *> &getGates() const;
    const int &getPassengers() const;
    Runway* getAvailableRunway();
    void addRunway(Runway* _runway);
    void printInfo(ofstream &output) const;
    void addPlaneToGate(Airplane *airplane, int gate);
    void removePlaneFromGate(Airplane *airplane);
    int findPlaneInGate(Airplane *airplane);
    void setRunways(const vector<Runway *> &runways);
};


#endif //AIRPORTSIM_AIRPORT_H
