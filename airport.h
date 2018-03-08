//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_AIRPORT_H
#define AIRPORTSIM_AIRPORT_H

#include <iostream>
#include "runway.h"
#include "gate.h"
#include <vector>
#include <fstream>
using namespace std;


class Airport {
    string name;
    string iata;
    string callsign;
    vector<Runway*> runways;
    vector<Gate*> gates;
    int passengers;
public:
    void setName(string _name);
    void setIata(string _iata);
    void setCallsign(string _callsign);
    void addGate(Gate* _gate);
    void setPassengers(int _passengers);
    string getName();
    string getIata();
    Runway* getAvailableRunway();
    void addRunway(Runway* _runway);
    void printInfo(ofstream &output);
    void printTestingInfo();
};


#endif //AIRPORTSIM_AIRPORT_H
