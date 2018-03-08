//
// Created by lena on 3/8/18.
//

#ifndef AIRPORTSIM_GATE_H
#define AIRPORTSIM_GATE_H


#include "airplane.h"

class Gate {
    Airplane* airplane;
public:
    bool isEmpty();
    Gate();
};


#endif //AIRPORTSIM_GATE_H
