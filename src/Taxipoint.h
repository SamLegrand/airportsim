//
// Created by sam on 27.04.18.
//

#ifndef AIRPORTSIM_TAXIPOINT_H
#define AIRPORTSIM_TAXIPOINT_H


#include "airplane.h"

class Airplane;

class Taxipoint {
private:
    std::string name;
    Airplane* planeToGate;
    Airplane* planeToRunway;
public:
    explicit Taxipoint(const std::string &name);
    const std::string &getName() const;
    void setName(const std::string &name);
    Airplane *getPlaneToGate() const;
    void setPlaneToGate(Airplane *planeToGate);
    Airplane *getPlaneToRunway() const;
    void setPlaneToRunway(Airplane *planeToRunway);
};


#endif //AIRPORTSIM_TAXIPOINT_H
