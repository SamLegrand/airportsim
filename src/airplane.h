//
// Created by sam on 01.03.18.
//

#ifndef AIRPORTSIM_AIRPLANE_H
#define AIRPORTSIM_AIRPLANE_H

#include <iostream>
#include <fstream>
#include "DesignByContract.h"

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

    /**
     * REQUIRE(this->getStatus() == "Approaching", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Descending", "Plane hasn't been set to the correct state.");
     */
    void approach(ostream &output, const string& airport);

    /**
     * REQUIRE(this->getStatus() == "Descending", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Landing" || this->getStatus() == "Descending", "Plane hasn't been set to the correct state.");
     */
    void descend(ostream &output);

    /**
     * REQUIRE(this->getStatus() == "Landing", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Landed", "Plane hasn't been set to the correct state.");
     */
    void land(ostream &output, const string& airport, const string& runway);

    /**
     * REQUIRE(this->getStatus() == "Landed", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Taxiing to Gate", "Plane hasn't been set to the correct state.");
     */
    void landed(ostream &output, const string& airport, const string& runway);

    /**
     * REQUIRE(this->getStatus() == "Taxiing to Gate", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Unboarding Plane", "Plane hasn't been set to the correct state.");
     */
    void taxiToGate(ostream &output, int gate);

    /**
     * REQUIRE(this->getStatus() == "Unboarding Plane", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Checking Plane", "Plane hasn't been set to the correct state.");
     */
    void unboardPlane(ostream &output, const string& airport, int gate);

    /**
     * REQUIRE(this->getStatus() == "Checking Plane", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Refueling Plane", "Plane hasn't been set to the correct state.");
     */
    void checkPlane(ostream &output);

    /**
     * REQUIRE(this->getStatus() == "Refueling Plane", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Boarding Plane", "Plane hasn't been set to the correct state.");
     */
    void refuelPlane(ostream &output);

    /**
     * REQUIRE(this->getStatus() == "Boarding Plane", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Standing at Gate", "Plane hasn't been set to the correct state.");
     */
    void boardPlane(ostream &output, const string& airport, int gate);

    /**
     * REQUIRE(this->getStatus() == "Standing at Gate", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Taxiing to Runway", "Plane hasn't been set to the correct state.");
     */
    void stand(ostream &output, int gate);

    /**
     * REQUIRE(this->getStatus() == "Taxiing to Runway", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Taking Off", "Plane hasn't been set to the correct state.");
     */
    void taxiToRunway(ostream &output, const string& runway);

    /**
     * REQUIRE(this->getStatus() == "Taking Off", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Ascending", "Plane hasn't been set to the correct state.");
     */
    void takeOff(ostream &output, const string& airport, const string& runway);

    /**
     * REQUIRE(this->getStatus() == "Ascending", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Leaving Airport" || this->getStatus() == "Ascending", "Plane hasn't been set to the correct state.");
     */
    void ascend(ostream &output);

    /**
     * REQUIRE(this->getStatus() == "Leaving Airport", "Plane wasn't in correct state.");
     * ENSURE(this->getStatus() == "Travelling", "Plane hasn't been set to the correct state.");
     */
    void leaveAirport(ostream &output, const string& airport);
};


#endif //AIRPORTSIM_AIRPLANE_H
