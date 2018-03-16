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
    void setName(const string &name);
    const string getName() const;
    bool isEmpty() const;
};


#endif //AIRPORTSIM_RUNWAY_H
