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
    void setNumber(const string &number);
    void setCallsign(const string &callsign);
    void setModel(const string &model);
    void setStatus(const string &status);
    void setPassengers(int passengers);
    void setFuel(int fuel);
    void setHeight(int height);
    const string &getNumber() const;
    const string &getModel() const;
    const string &getStatus() const;
    int getPassengers() const;
    int getFuel() const;
    int getHeight() const;
    const string &getCallsign() const;
    void printInfo(ofstream &output);
    void printTestingInfo();

    /**
     \n REQUIRE(this->getStatus() == "Approaching", "Plane wasn't in correct state.");
     */
    void approach(string airport);

    /**
     \n REQUIRE(this->getStatus() == "Descending", "Plane wasn't in correct state.");
     */
    void descend();

    /**
     \n REQUIRE(this->getStatus() == "Landing", "Plane wasn't in correct state.");
     */
    void land(string airport, string runway);

    /**
     \n REQUIRE(this->getStatus() == "Landed", "Plane wasn't in correct state.");
     */
    void landed(string airport, string runway);

    /**
     \n REQUIRE(this->getStatus() == "Awaiting Taxi", "Plane wasn't in correct state.");
     */
    void taxiToGate(int gate);

    /**
     \n REQUIRE(this->getStatus() == "Taxiing to Gate", "Plane wasn't in correct state.");
     */
    void stand(int gate);

    /**
     \n REQUIRE(this->getStatus() == "Standing at Gate", "Plane wasn't in correct state.");
     */
    void unboardPlane(string airport, int gate);

    /**
     \n REQUIRE(this->getStatus() == "Unboarded Plane", "Plane wasn't in correct state.");
     */
    void checkPlane();

    /**
     \n REQUIRE(this->getStatus() == "Checked Plane", "Plane wasn't in correct state.");
     */
    void refuelPlane();

    /**
     \n REQUIRE(this->getStatus() == "Refueled Plane", "Plane wasn't in correct state.");
     */
    void boardPlane(string airport, int gate);

    /**
     \n REQUIRE(this->getStatus() == "Boarded Plane", "Plane wasn't in correct state.");
     */
    void taxiToRunway(string runway);

    /**
     \n REQUIRE(this->getStatus() == "Taxiing to Runway", "Plane wasn't in correct state.");
     */
    void takeOff(string airport, string runway);

    /**
     \n REQUIRE(this->getStatus() == "Ascending", "Plane wasn't in correct state.");
     */
    void ascend();

    /**
     \n REQUIRE(this->getStatus() == "Leaving Airport", "Plane wasn't in correct state.");
     */
    void leaveAirport(string airport);
};


#endif //AIRPORTSIM_AIRPLANE_H
