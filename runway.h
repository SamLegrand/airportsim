//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_RUNWAY_H
#define AIRPORTSIM_RUNWAY_H

#include <iostream>
using namespace std;

class Runway {
    string name;
    string airport;
public:
    void setName(string _name);
    void setAirport(string _airport);
    void printInfo();
};


#endif //AIRPORTSIM_RUNWAY_H
