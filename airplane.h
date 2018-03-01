//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_AIRPLANE_H
#define AIRPORTSIM_AIRPLANE_H

#include <iostream>
using namespace std;

class Airplane {
    string number;
    string callsign;
    string model;
    string status;
    int passengers;
    int fuel;
public:
    void setNumber(string _number);
    void setCallsign(string _callsign);
    void setModel(string _model);
    void setStatus(string _status);
    void setPassengers(int _passengers);
    void setFuel(int _fuel);
    void printInfo();
};


#endif //AIRPORTSIM_AIRPLANE_H
