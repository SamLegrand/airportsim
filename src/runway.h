//
// Created by lena on 3/29/18.
//

#ifndef AIRPORTSIM_RUNWAY_H
#define AIRPORTSIM_RUNWAY_H

#include "airplane.h"
#include <string>
#include <vector>

class Airplane;

class Runway {
    Runway* initCheck;
    std::string name;
    std::string type;
    int length;
    Airplane* airplane;
    Airplane* taxipointToRunway;
    Airplane* taxipointToGate;
    Airplane* crossing;
    std::string taxipoint;
public:
    /**
     * ENSURE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     */
    Runway();
    /**
     *
     * @return
     */
    bool properlyInitialized();

    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * ENSURE(this->getTaxipointToRunway() == taxipointToRunway, "Plane wasn't correctly added to taxipointToRunway");
     * @return
     */
    Airplane *getTaxipointToRunway();
    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @param taxipointToRunway
     */
    void setTaxipointToRunway(Airplane *taxipointToRunway);

    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @return
     */
    Airplane *getTaxipointToGate();
    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * ENSURE(this->getTaxipointToGate() == taxipointToGate, "Plane wasn't correctly added to taxipointToGate");
     * @param taxipointToGate
     */
    void setTaxipointToGate(Airplane *taxipointToGate);

    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @return
     */
    Airplane *getAirplaneCrossing();
    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * ENSURE(this->getAirplaneCrossing() == crossing, "Plane wasn't correctly added to crossing");
     * @param crossing
     */
    void setAirplaneCrossing(Airplane *crossing);

    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @return
     */
    const std::string &getTaxipoint();
    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * ENSURE(this->getTaxipoint() == taxipoint, "Taxipoint name wasn't set properly.");
     * @param taxipoint
     */
    void setTaxipoint(const std::string &taxipoint);

    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @return
     */
    const std::string &getName();
    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @param name
     */
    void setName(const std::string &name);

    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @return
     */
    Airplane *getAirplane();
    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @param airplane
     */
    void setAirplane(Airplane *airplane);

    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @return
     */
    const std::string &getType();
    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @param type
     */
    void setType(const std::string &type);

    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @return
     */
    int getLength();
    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @param length
     */
    void setLength(int length);

    /**
     * REQUIRE(this->properlyInitialized(), "Runway wasn't properly initialized.");
     * @return
     */
    bool ableToCross();
};


#endif //AIRPORTSIM_RUNWAY_H
