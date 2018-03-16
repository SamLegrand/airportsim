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
    void setName(string _name);
    void setIata(string _iata);
    void setCallsign(string _callsign);
    void setGates(int _gate);
    int getAvailableGate();
    void setPassengers(int _passengers);
    string getName();
    string getIata();
    Runway* getAvailableRunway();
    void addRunway(Runway* _runway);
    void printInfo(ofstream &output);
    void addPlane(Airplane* airplane, int gate);
    void removePlane(Airplane* airplane);
    void printTestingInfo();
};


#endif //AIRPORTSIM_AIRPORT_H
