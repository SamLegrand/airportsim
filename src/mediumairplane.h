//
// Created by sam on 16.05.18.
//

#ifndef AIRPORTSIM_MEDIUMAIRPLANE_H
#define AIRPORTSIM_MEDIUMAIRPLANE_H


#include "airplane.h"

class MediumAirplane: public Airplane {
public:
    /**
     * ENSURE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     */
    MediumAirplane(): Airplane(){
        ENSURE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    }

    /**
     * ENSURE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     * @param airplane
     */
    explicit MediumAirplane(Airplane* airplane): Airplane(airplane){
        ENSURE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
    }

    /**
     * REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     * REQUIRE(this->getStatus() == "Unboarding Plane", "Medium plane has to the be in correct state.");
     * ENSURE(this->getStatus() == "Checking Plane" || this->getStatus() == "Unboarding Plane", "Medium plane should be set to the correct state.");
     * @param output
     * @param airport
     * @param gate
     */
    virtual void unboardPlane(std::ostream &output, const std::string& airport, int gate);

    /**
     * REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     * REQUIRE(this->getStatus() == "Checking Plane", "Medium plane has to the be in correct state.");
     * ENSURE(this->getStatus() == "Refueling Plane" || this->getStatus() == "Checking Plane", "Medium plane should be set to the correct state.");
     * @param output
     */
    virtual void checkPlane(std::ostream &output);

    /**
     * REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     * REQUIRE(this->getStatus() == "Boarding Plane", "Medium plane has to the be in correct state.");
     * ENSURE(this->getStatus() == "Standing at Gate" || this->getStatus() == "Boarding Plane", "Medium plane should be set to the correct state.");
     * @param output
     * @param airport
     * @param gate
     */
    virtual void boardPlane(std::ostream &output, const std::string& airport, int gate);

    /**
     * REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     * REQUIRE(this->getStatus() == "Pushing back", "Medium plane has to the be in correct state.");
     * ENSURE(this->getStatus() == "Taxiing to Runway" || this->getStatus() == "Pushing back", "Medium plane should be set to the correct state.");
     * @param output
     */
    virtual void pushBack(std::ostream &output);

    /**
     * REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     */
    virtual void consumeFuel();

    /**
     * REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     * REQUIRE(this->getStatus() == "Emergency Unboarding", "Medium plane has to the be in correct state.");
     * ENSURE(this->getStatus() == "Emergency Checking" || this->getStatus() == "Emergency Unboarding", "Medium plane should be set to the correct state.");
     * @param output
     * @param airport
     * @param runway
     */
    virtual void unboardAtRunway(std::ostream &output, const std::string &airport, const std::string &runway);

    /**
     * REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     * REQUIRE(this->getStatus() == "Emergency Checking", "Medium plane has to the be in correct state.");
     * ENSURE(this->getStatus() == "Emergency Refueling" || this->getStatus() == "Emergency Checking", "Medium plane should be set to the correct state.");
     * @param output
     */
    virtual void checkAtRunway(std::ostream &output);

    /**
     * REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     * REQUIRE(this->getStatus() == "Emergency Refueling", "Medium plane has to the be in correct state.");
     * ENSURE(this->getStatus() == "Landed", "Medium plane should be set to the correct state.");
     * @param output
     */
    virtual void refuelAtRunway(std::ostream &output);

    /**
     * REQUIRE(this->properlyInitialized(), "Medium plane wasn't properly initialized.");
     * REQUIRE(this->getStatus() == "Refueling Plane", "Medium plane has to the be in correct state.");
     * ENSURE(this->getStatus() == "Boarding Plane", "Medium plane should be set to the correct state.");
     * @param output
     */
    virtual void refuelPlane(std::ostream &output);
};


#endif //AIRPORTSIM_MEDIUMAIRPLANE_H
