//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_AIRPORT_H
#define AIRPORTSIM_AIRPORT_H

#include <iostream>
#include "runway.h"
#include <vector>
using namespace std;

class Airport {
    string name;
    string iata;
    string callsign;
    vector<Runway*> runways;
    int gates;
    int passengers;
public:
    void setName(string _name);
    void setIata(string _iata);
    void setCallsign(string _callsign);
    void setGates(int _gates);
    void setPassengers(int _passengers);
    string getName();
    void addRunway(Runway* _runway);
    void printInfo();
    void printTestingInfo();
};


#endif //AIRPORTSIM_AIRPORT_H
