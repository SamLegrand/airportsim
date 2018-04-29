//
// Created by sam on 16.03.18.
//

#include <iostream>
#include <gtest/gtest.h>

#include "AirportSim.h"

class AirportSimDomainTest: public ::testing::Test {
protected:
    virtual void SetUp(){

    }
    virtual void TearDown(){

    }
    Airplane airplane_;
    Airport airport_;
};

TEST_F(AirportSimDomainTest, LandingScenario){      //Testing landin scenario
    airplane_.setNumber("N11842");
    airplane_.setCallsign("Cessna 842");
    airplane_.setModel("Cessna 340");
    airplane_.setStatus("Approaching");
    airplane_.setPassengers(60);
    airplane_.setFuel(20);
    EXPECT_EQ(airplane_.getStatus(), "Approaching");
    std::ostringstream stream;      //Using stream to check output
    airplane_.approach(stream, "Antwerp International Airport");    //Check for correct output for approach
    EXPECT_EQ(stream.str(), "Cessna 842 is approaching Antwerp International Airport at 10000 ft.\n");
    EXPECT_EQ(airplane_.getStatus(), "Descending");
    EXPECT_EQ(airplane_.getHeight(), 10000);
    stream.str(std::string());      //Clear stream
    airplane_.descendTo5k(stream);      //Check for correct output for descendTo5k
    EXPECT_EQ(stream.str(), "Cessna 842 descended to 9000 ft.\n");
    EXPECT_EQ(airplane_.getHeight(), 9000);
    while(airplane_.getHeight() >= 2000){
        airplane_.descendTo5k(stream);
    }
    stream.str(std::string());
    EXPECT_EQ(airplane_.getStatus(), "Landing");
    airplane_.land(stream, "Antwerp International Airport", "11R");
    EXPECT_EQ(stream.str(), "Cessna 842 is landing at Antwerp International Airport on runway 11R\n");
    EXPECT_EQ(airplane_.getHeight(), 0);
    EXPECT_EQ(airplane_.getStatus(), "Landed");
    stream.str(std::string());
    airplane_.landed(stream, "Antwerp International Airport", "11R");   //Check for correct output for landed
    EXPECT_EQ(stream.str(), "Cessna 842 has landed at Antwerp International Airport on runway 11R\n");
    EXPECT_EQ(airplane_.getStatus(), "Taxiing to Gate");
    stream.str(std::string());
    airplane_.taxiToGate(stream, 1);    //Check for correct output for taxiToGate
    EXPECT_EQ(stream.str(), "Cessna 842 is taxiing to Gate 1\n");
    EXPECT_EQ(airplane_.getStatus(), "Unboarding Plane");
}

TEST_F(AirportSimDomainTest, ArrivalAtGateScenario){        //Testing arrival at gate scenario
    airplane_.setNumber("N11842");
    airplane_.setCallsign("Cessna 842");
    airplane_.setModel("Cessna 340");
    airplane_.setStatus("Unboarding Plane");
    airplane_.setPassengers(60);
    airplane_.setFuel(20);
    EXPECT_EQ(airplane_.getStatus(), "Unboarding Plane");
    std::ostringstream stream;
    airplane_.unboardPlane(stream, "Antwerp International Airport", 1);     //Check for correct output for unboardPlane
    EXPECT_EQ(stream.str(), "60 passengers exited Cessna 842 at gate 1 of Antwerp International Airport\n");
    EXPECT_EQ(airplane_.getStatus(), "Checking Plane");
    stream.str(std::string());
    airplane_.checkPlane(stream);       //Check for correct output for checkPlane
    EXPECT_EQ(stream.str(), "Cessna 842 has been checked for technical malfunctions\n");
    EXPECT_EQ(airplane_.getStatus(), "Refueling Plane");
    stream.str(std::string());
    airplane_.refuelPlane(stream);      //Check for correct output for refuelPlane
    EXPECT_EQ(stream.str(), "Cessna 842 has been refueled\n");
    EXPECT_EQ(airplane_.getStatus(), "Boarding Plane");
    stream.str(std::string());
    airplane_.boardPlane(stream, "Antwerp International Airport", 1);       //Check for correct output for boardPlane
    EXPECT_EQ(stream.str(), "60 passengers boarded Cessna 842 at gate 1 of Antwerp International Airport\n");
    EXPECT_EQ(airplane_.getStatus(), "Standing at Gate");
}

TEST_F(AirportSimDomainTest, TakeOffScenario){      //Testing takeoff scenario
    airplane_.setNumber("N11842");
    airplane_.setCallsign("Cessna 842");
    airplane_.setModel("Cessna 340");
    airplane_.setStatus("Standing at Gate");
    airplane_.setPassengers(60);
    airplane_.setFuel(20);
    EXPECT_EQ(airplane_.getStatus(), "Standing at Gate");
    std::ostringstream stream;
    airplane_.stand(stream, 1);     //Check for correct output for stand
    EXPECT_EQ(stream.str(), "Cessna 842 is standing at Gate 1\n");
    EXPECT_EQ(airplane_.getStatus(), "Taxiing to Runway");
    EXPECT_EQ(airplane_.getHeight(), 0);
    stream.str(std::string());
    airplane_.taxiToRunway(stream, "11R");      //Check for correct output for taxiToRunway
    EXPECT_EQ(stream.str(), "Cessna 842 is taxiing to runway 11R\n");
    EXPECT_EQ(airplane_.getStatus(), "Taking Off");
    stream.str(std::string());
    airplane_.takeOff(stream, "Antwerp International Airport", "11R");
    EXPECT_EQ(stream.str(), "Cessna 842 is taking off at Antwerp International Airport on runway 11R\n");
    EXPECT_EQ(airplane_.getStatus(), "Ascending");
    stream.str(std::string());
    airplane_.ascend(stream);       //Check for correct output for ascend
    EXPECT_EQ(stream.str(), "Cessna 842 ascended to 1000 ft.\n");
    while(airplane_.getHeight() <= 4000){
        airplane_.ascend(stream);
    }
    EXPECT_EQ(airplane_.getStatus(), "Leaving Airport");
    stream.str(std::string());
    airplane_.leaveAirport(stream, "Antwerp International Airport");    //Check for correct output for leaveAirport
    EXPECT_EQ(airplane_.getStatus(), "Travelling");
}

TEST_F(AirportSimDomainTest, ContractViolations){       //Testing for various contract violations
    airport_.setGates(0);   //set gate amount to 0
    EXPECT_DEATH(airport_.addPlaneToGate(&airplane_, 1), "Assertion.*failed");      //Impossible to add because there are no gates
    airport_.setGates(1);
    EXPECT_DEATH(airport_.addPlaneToGate(&airplane_, 0), "Assertion.*failed");      //Impossible to add (gates start at 1)
    airplane_.setStatus("Unknown");
    std::ostringstream stream;
    EXPECT_DEATH(airplane_.approach(stream, ""), "Assertion.*failed");      //Checking for current state violations for all airplane functions
    EXPECT_DEATH(airplane_.descendTo5k(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane_.land(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane_.landed(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane_.taxiToGate(stream, 1), "Assertion.*failed");
    EXPECT_DEATH(airplane_.unboardPlane(stream, "", 1), "Assertion.*failed");
    EXPECT_DEATH(airplane_.checkPlane(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane_.refuelPlane(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane_.boardPlane(stream, "", 1), "Assertion.*failed");
    EXPECT_DEATH(airplane_.stand(stream, 1), "Assertion.*failed");
    EXPECT_DEATH(airplane_.taxiToRunway(stream, ""), "Assertion.*failed");
    EXPECT_DEATH(airplane_.takeOff(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane_.ascend(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane_.leaveAirport(stream, ""), "Assertion.*failed");
}

TEST_F(AirportSimDomainTest, AirportOccupation){        //Testing specific airport functions for gates and runways
    airport_.setGates(1);
    EXPECT_EQ(airport_.getGates(), 1);      //Expect that there is one gate in airport
    airport_.addPlaneToGate(&airplane_, 1);
    EXPECT_EQ(airport_.getAvailableGate(), -1);     //There are no gates available, expect -1
    airport_.removePlaneFromGate(&airplane_);
    EXPECT_EQ(airport_.getAvailableGate(), 1);      //Expect that gate 1 is now available
    Runway* r = new Runway;
    r->setName("11R");
    airport_.addRunway(r);
    EXPECT_EQ(airport_.getAvailableRunway()->getName(), "11R");      //Expect that runway 11R is available
    r->setAirplane(&airplane_);
    EXPECT_TRUE(airport_.getAvailableRunway() == NULL);     //Expect that there is no runway available
    EXPECT_EQ(airport_.findPlaneInRunway(&airplane_)->getName(), "11R");     //Expect that airplane is currently using runway 11R
}
