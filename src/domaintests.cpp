//
// Created by sam on 16.03.18.
//

#include <iostream>
#include <gtest/gtest.h>

#include "AirportSim.h"
#include "importer.h"
#include "utils.h"
#include "Exporter.h"

class AirportSimDomainTest: public ::testing::Test {
protected:
    virtual void SetUp(){

    }
    virtual void TearDown(){

    }
    Airplane airplane;
    SmallAirplane smallairplane;
    Airport airport;
    Runway runway;
    AirportSim simulation;
    Exporter exporter;
};

TEST_F(AirportSimDomainTest, DefaultConstructorSim){
    // Verify correct initialization
    EXPECT_TRUE(simulation.properlyInitialized());
    EXPECT_EQ(simulation.getAirleaderoutput(), "../AirControlOutput.txt");
    EXPECT_EQ(simulation.getAirplanes().size(), (unsigned int)0);
    EXPECT_EQ(simulation.getAirports().size(), (unsigned int)0);
}

TEST_F(AirportSimDomainTest, FunctionsSim){
    std::ofstream errstream;
    ASSERT_TRUE(DirectoryExists("../testInput"));
    importer::importAirport("../testInput/inputlegal.xml", errstream, simulation);

    // Verify checkSimEnd()
    EXPECT_EQ(simulation.checkSimEnd(), false);
    simulation.simulate(errstream);
    EXPECT_EQ(simulation.checkSimEnd(), true);
}

TEST_F(AirportSimDomainTest, DefaultConstructorAirport){
    // Verify correct initialization
    EXPECT_TRUE(airport.properlyInitialized());
    EXPECT_TRUE(airport.getH3000() == NULL);
    EXPECT_TRUE(airport.getH5000() == NULL);
}

TEST_F(AirportSimDomainTest, FunctionsAirport){
    // Verify gate helper functions
    airport.setGates(1);
    airport.addPlaneToGate(&airplane, 1);
    EXPECT_EQ(airport.findPlaneInGate(&airplane), 1);
    airport.removePlaneFromGate(&airplane);
    EXPECT_EQ(airport.findPlaneInGate(&airplane), -1);

    // Verify runway helper functions
    runway.setName("RunwayTest");
    airport.addRunway(&runway);
    runway.setAirplane(&airplane);
    EXPECT_EQ(airport.findPlaneInRunway(&airplane), &runway);
    airport.removePlaneFromRunway(&airplane);
    EXPECT_TRUE(airport.findPlaneInRunway(&airplane) == NULL);
    EXPECT_EQ(airport.findRunwayByRunwayName("RunwayTest"), &runway);

    // Verify crossing helper functions
    runway.setAirplaneCrossing(&airplane);
    EXPECT_EQ(airport.findPlaneInCrossing(&airplane), &runway);
    runway.setAirplaneCrossing(NULL);

    // Verify taxipoint helper functions
    runway.setTaxipoint("Alpha");
    EXPECT_EQ(airport.findRunwayByTaxiName("Alpha"), &runway);
    runway.setTaxipointToGate(&airplane);
    runway.setTaxipointToRunway(&airplane);
    EXPECT_EQ(airport.findRunwayByTaxipointToGate(&airplane), &runway);
    EXPECT_EQ(airport.findRunwayByTaxipointToRunway(&airplane), &runway);
    Runway runway2;
    runway2.setTaxipoint("Bravo");
    airport.addRunway(&runway2);
    EXPECT_EQ(airport.findNextRunwayToGate(&runway), &runway2);
}

TEST_F(AirportSimDomainTest, DefaultConstructorAirplane){
    // Verify correct initialization
    EXPECT_TRUE(airplane.properlyInitialized());
    EXPECT_EQ(airplane.getTime(), 0);
    EXPECT_TRUE(airplane.isCommunicating());
    EXPECT_EQ(airplane.getSquawk(), 0);
}

TEST_F(AirportSimDomainTest, DefaultConstructorRunway){
    // Verify correct initialization
    EXPECT_TRUE(runway.properlyInitialized());
    EXPECT_EQ(runway.getName(), "");
    EXPECT_TRUE(runway.getAirplane() == NULL);
    EXPECT_TRUE(runway.getAirplaneCrossing() == NULL);
    EXPECT_TRUE(runway.getTaxipointToGate() == NULL);
    EXPECT_TRUE(runway.getTaxipointToRunway() == NULL);
}

TEST_F(AirportSimDomainTest, FunctionsRunway){
    // Verify ableToCross()
    EXPECT_TRUE(runway.ableToCross());
    runway.setAirplaneCrossing(&airplane);
    EXPECT_FALSE(runway.ableToCross());
    runway.setAirplaneCrossing(NULL);
    airplane.setStatus("Ready for Takeoff");
    runway.setAirplane(&airplane);
    EXPECT_TRUE(runway.ableToCross());
    airplane.setStatus("Taking Off");
    EXPECT_FALSE(runway.ableToCross());
}

TEST_F(AirportSimDomainTest, DefaultConstructorExporter){
    // Verify correct initialization
    EXPECT_TRUE(exporter.properlyInitialized());
}

TEST_F(AirportSimDomainTest, ContractViolations){       //Testing for various contract violations
    airport.setGates(0);   //set gate amount to 0
    EXPECT_DEATH(airport.addPlaneToGate(&airplane, 1), "Assertion.*failed");      //Impossible to add because there are no gates
    EXPECT_DEATH(airport.findPlaneInGate(&airplane), "Assertion.*failed");
    EXPECT_DEATH(airport.getAvailableGate(), "Assertion.*failed");
    EXPECT_DEATH(airport.removePlaneFromGate(&airplane), "Assertion.*failed");
    EXPECT_DEATH(airport.findPlaneInRunway(&airplane), "Assertion.*failed");
    EXPECT_DEATH(airport.findPlaneInCrossing(&airplane), "Assertion.*failed");
    EXPECT_DEATH(airport.getRunwayByAirplane(&airplane), "Assertion.*failed");
    EXPECT_DEATH(airport.findNextRunwayToRunway(&runway), "Assertion.*failed");
    EXPECT_DEATH(airport.findNextRunwayToGate(&runway), "Assertion.*failed");
    EXPECT_DEATH(airport.findRunwayByTaxipointToRunway(&airplane), "Assertion.*failed");
    EXPECT_DEATH(airport.findRunwayByTaxipointToGate(&airplane), "Assertion.*failed");
    EXPECT_DEATH(airport.findNearestAvailableRunway(&airplane), "Assertion.*failed");
    EXPECT_DEATH(airport.getRunwayByAirplane(&airplane), "Assertion.*failed");
    EXPECT_DEATH(airport.findRunwayByTaxiName(""), "Assertion.*failed");
    EXPECT_DEATH(airport.findRunwayByRunwayName(""), "Assertion.*failed");
    airport.setGates(1);
    EXPECT_DEATH(airport.addPlaneToGate(&airplane, 0), "Assertion.*failed");      //Impossible to add (gates start at 1)
    airplane.setStatus("Unknown");
    std::ostringstream stream;
    EXPECT_DEATH(airplane.approach(stream, ""), "Assertion.*failed");      //Checking for current state violations for all airplane functions
    EXPECT_DEATH(airplane.flyWaitPattern(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane.descendTo5k(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane.descendTo3k(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane.finalapproach(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane.land(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane.landed(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane.taxiToGate(stream, 1), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.unboardPlane(stream, "", 1), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.checkPlane(stream), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.refuelPlane(stream), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.boardPlane(stream, "", 1), "Assertion.*failed");
    EXPECT_DEATH(airplane.stand(stream, 1), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.pushBack(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane.taxiToRunway(stream, ""), "Assertion.*failed");
    EXPECT_DEATH(airplane.readyForTakeoff(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane.takeOff(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane.ascend(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane.leaveAirport(stream, ""), "Assertion.*failed");

}

//TEST_F(AirportSimDomainTest, LandingScenario){      //Testing landing scenario
//    airplane_.setNumber("N11842");
//    airplane_.setCallsign("Cessna 842");
//    airplane_.setModel("Cessna 340");
//    airplane_.setStatus("Approaching");
//    airplane_.setPassengers(60);
//    airplane_.setFuel(20);
//    airplane_.setEngine("jet");
//    airplane_.setType("airline");
//    airplane_.setSize("large");
//    EXPECT_EQ(airplane_.getStatus(), "Approaching");
//    std::ostringstream stream;      //Using stream to check output
//    airplane_.approach(stream, "Antwerp International Airport");    //Check for correct output for approach
//    EXPECT_EQ(stream.str(), "Cessna 842 is approaching Antwerp International Airport at 10000 ft.\n");
//    EXPECT_EQ(airplane_.getStatus(), "Descending to 5k");
//    EXPECT_EQ(airplane_.getHeight(), 10000);
//    stream.str(std::string());      //Clear stream
//    airplane_.descendTo5k(stream);      //Check for correct output for descendTo5k
//    EXPECT_EQ(stream.str(), "Cessna 842 descended to 9000 ft.\n");
//    EXPECT_EQ(airplane_.getHeight(), 9000);
//    while(airplane_.getHeight() > 5000){
//        airplane_.descendTo5k(stream);
//    }
//    stream.str(std::string());
//    EXPECT_EQ(airplane_.getStatus(), "Flying wait pattern");
//    airplane_.setStatus("Descending to 3k");
//    while(airplane_.getHeight() > 3000){
//        airplane_.descendTo3k(stream);
//    }
//    stream.str(std::string());
//    airplane_.setStatus("Final Approach");
//    airplane_.finalapproach(stream, "Antwerp International Airport", "11R");
//    stream.str(std::string());
//    airplane_.setStatus("Landing");
//    EXPECT_EQ(airplane_.getStatus(), "Landing");
//    airplane_.land(stream, "Antwerp International Airport", "11R");
//    EXPECT_EQ(stream.str(), "Cessna 842 is landing at Antwerp International Airport on runway 11R\n");
//    EXPECT_EQ(airplane_.getHeight(), 0);
//    EXPECT_EQ(airplane_.getStatus(), "Landed");
//    stream.str(std::string());
//    airplane_.landed(stream, "Antwerp International Airport", "11R");   //Check for correct output for landed
//    EXPECT_EQ(stream.str(), "Cessna 842 has landed at Antwerp International Airport on runway 11R\n");
//    EXPECT_EQ(airplane_.getStatus(), "Taxiing to Gate");
//    stream.str(std::string());
//    airplane_.taxiToGate(stream, 1);    //Check for correct output for taxiToGate
//    EXPECT_EQ(stream.str(), "Cessna 842 is taxiing to Gate 1\n");
//    EXPECT_EQ(airplane_.getStatus(), "Unboarding Plane");
//}
//
//TEST_F(AirportSimDomainTest, ArrivalAtGateScenario){        //Testing arrival at gate scenario
//    airplane_.setNumber("N11842");
//    airplane_.setCallsign("Cessna 842");
//    airplane_.setModel("Cessna 340");
//    airplane_.setStatus("Unboarding Plane");
//    airplane_.setPassengers(60);
//    airplane_.setFuel(20);
//    EXPECT_EQ(airplane_.getStatus(), "Unboarding Plane");
//    std::ostringstream stream;
//    airplane_.unboardPlane(stream, "Antwerp International Airport", 1);     //Check for correct output for unboardPlane
//    EXPECT_EQ(stream.str(), "60 passengers exited Cessna 842 at gate 1 of Antwerp International Airport\n");
//    EXPECT_EQ(airplane_.getStatus(), "Checking Plane");
//    stream.str(std::string());
//    airplane_.checkPlane(stream);       //Check for correct output for checkPlane
//    EXPECT_EQ(stream.str(), "Cessna 842 has been checked for technical malfunctions\n");
//    EXPECT_EQ(airplane_.getStatus(), "Refueling Plane");
//    stream.str(std::string());
//    airplane_.refuelPlane(stream);      //Check for correct output for refuelPlane
//    EXPECT_EQ(stream.str(), "Cessna 842 has been refueled\n");
//    EXPECT_EQ(airplane_.getStatus(), "Boarding Plane");
//    stream.str(std::string());
//    airplane_.boardPlane(stream, "Antwerp International Airport", 1);       //Check for correct output for boardPlane
//    EXPECT_EQ(stream.str(), "60 passengers boarded Cessna 842 at gate 1 of Antwerp International Airport\n");
//    EXPECT_EQ(airplane_.getStatus(), "Standing at Gate");
//}
//
//TEST_F(AirportSimDomainTest, TakeOffScenario){      //Testing takeoff scenario
//    airplane_.setNumber("N11842");
//    airplane_.setCallsign("Cessna 842");
//    airplane_.setModel("Cessna 340");
//    airplane_.setStatus("Standing at Gate");
//    airplane_.setPassengers(60);
//    airplane_.setFuel(20);
//    EXPECT_EQ(airplane_.getStatus(), "Standing at Gate");
//    std::ostringstream stream;
//    airplane_.stand(stream, 1);     //Check for correct output for stand
//    EXPECT_EQ(stream.str(), "Cessna 842 is standing at Gate 1\n");
//    EXPECT_EQ(airplane_.getStatus(), "Taxiing to Runway");
//    EXPECT_EQ(airplane_.getHeight(), 0);
//    stream.str(std::string());
//    airplane_.taxiToRunway(stream, "11R");      //Check for correct output for taxiToRunway
//    EXPECT_EQ(stream.str(), "Cessna 842 is taxiing to runway 11R\n");
//    EXPECT_EQ(airplane_.getStatus(), "Taking Off");
//    stream.str(std::string());
//    airplane_.takeOff(stream, "Antwerp International Airport", "11R");
//    EXPECT_EQ(stream.str(), "Cessna 842 is taking off at Antwerp International Airport on runway 11R\n");
//    EXPECT_EQ(airplane_.getStatus(), "Ascending");
//    stream.str(std::string());
//    airplane_.ascend(stream);       //Check for correct output for ascend
//    EXPECT_EQ(stream.str(), "Cessna 842 ascended to 1000 ft.\n");
//    while(airplane_.getHeight() <= 4000){
//        airplane_.ascend(stream);
//    }
//    EXPECT_EQ(airplane_.getStatus(), "Leaving Airport");
//    stream.str(std::string());
//    airplane_.leaveAirport(stream, "Antwerp International Airport");    //Check for correct output for leaveAirport
//    EXPECT_EQ(airplane_.getStatus(), "Travelling");
//}
//
//TEST_F(AirportSimDomainTest, ContractViolations){       //Testing for various contract violations
//    airport_.setGates(0);   //set gate amount to 0
//    EXPECT_DEATH(airport_.addPlaneToGate(&airplane_, 1), "Assertion.*failed");      //Impossible to add because there are no gates
//    airport_.setGates(1);
//    EXPECT_DEATH(airport_.addPlaneToGate(&airplane_, 0), "Assertion.*failed");      //Impossible to add (gates start at 1)
//    airplane_.setStatus("Unknown");
//    std::ostringstream stream;
//    EXPECT_DEATH(airplane_.approach(stream, ""), "Assertion.*failed");      //Checking for current state violations for all airplane functions
//    EXPECT_DEATH(airplane_.descendTo5k(stream), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.land(stream, "", ""), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.landed(stream, "", ""), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.taxiToGate(stream, 1), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.unboardPlane(stream, "", 1), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.checkPlane(stream), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.refuelPlane(stream), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.boardPlane(stream, "", 1), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.stand(stream, 1), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.taxiToRunway(stream, ""), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.takeOff(stream, "", ""), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.ascend(stream), "Assertion.*failed");
//    EXPECT_DEATH(airplane_.leaveAirport(stream, ""), "Assertion.*failed");
//}
//

