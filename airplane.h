//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_AIRPLANE_H
#define AIRPORTSIM_AIRPLANE_H

#include <iostream>
#include <fstream>
#include "airport.h"
using namespace std;

class Airplane {
    string number;
    string callsign;
    string model;
    string status;
    int passengers;
    int fuel;
    int height;
public:
    void setNumber(string _number);
    void setCallsign(string _callsign);
    void setModel(string _model);
    void setStatus(string _status);
    void setPassengers(int _passengers);
    void setFuel(int _fuel);
    void setHeight(int height);
    string getStatus();
    void printInfo(ofstream &output);
    void printTestingInfo();
    void approach(string airport);
    void descend();
    void land(string airport, string runway);
    void landed(string airport, string runway);
    void taxiToGate(int gate);
    void stand(int gate);
    void taxiToRunway(string runway);
    void takeOff(string airport, string runway);
    void ascend();
    void leaveAirport(string airport);
    void boardPlane(string airport, int gate);
    void unboardPlane(string airport, int gate);
    void checkPlane();
    void refuelPlane();
};


#endif //AIRPORTSIM_AIRPLANE_H
