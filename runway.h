//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_RUNWAY_H
#define AIRPORTSIM_RUNWAY_H

#include <iostream>
using namespace std;

class Runway {
    string name;
    bool available;
public:
    void setName(string _name);
    string getName();
    void printInfo();
    bool isEmpty();
};


#endif //AIRPORTSIM_RUNWAY_H
