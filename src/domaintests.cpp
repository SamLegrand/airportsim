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
    MediumAirplane mediumairplane;
    LargeAirplane largeairplane;
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
    importer::importAirport("../testInput/inputlegal1.xml", errstream, simulation);

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
    EXPECT_DEATH(airplane.stand(stream, 1), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.pushBack(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane.taxiToRunway(stream, ""), "Assertion.*failed");
    EXPECT_DEATH(airplane.readyForTakeoff(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane.takeOff(stream, "", ""), "Assertion.*failed");
    EXPECT_DEATH(airplane.ascend(stream), "Assertion.*failed");
    EXPECT_DEATH(airplane.leaveAirport(stream, ""), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.unboardPlane(stream, "", 1), "Assertion.*failed");   //Check for inherited functions
    EXPECT_DEATH(smallairplane.checkPlane(stream), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.refuelPlane(stream), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.boardPlane(stream, "", 1), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.checkAtRunway(stream), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.refuelAtRunway(stream), "Assertion.*failed");
    EXPECT_DEATH(smallairplane.unboardAtRunway(stream, "", ""), "Assertion.*failed");
}

TEST_F(AirportSimDomainTest, FuelTest){
    std::ostringstream stream;
    smallairplane.setFuel(250); // Test small propeller
    smallairplane.setEngine("propeller");
    smallairplane.consumeFuel();
    EXPECT_EQ(smallairplane.getFuel(), 240);
    smallairplane.setStatus("Refueling Plane");
    smallairplane.refuelPlane(stream);
    EXPECT_EQ(smallairplane.getFuel(), 10240);
    smallairplane.setFuel(250); // Test small jet
    smallairplane.setEngine("jet");
    smallairplane.consumeFuel();
    EXPECT_EQ(smallairplane.getFuel(), 225);
    smallairplane.setStatus("Refueling Plane");
    smallairplane.refuelPlane(stream);
    EXPECT_EQ(smallairplane.getFuel(), 10225);
    mediumairplane.setFuel(250); // Test medium propeller
    mediumairplane.setEngine("propeller");
    mediumairplane.consumeFuel();
    EXPECT_EQ(mediumairplane.getFuel(), 200);
    mediumairplane.setStatus("Refueling Plane");
    mediumairplane.refuelPlane(stream);
    EXPECT_EQ(mediumairplane.getFuel(), 10200);
    mediumairplane.setFuel(250); // Test medium jet
    mediumairplane.setEngine("jet");
    mediumairplane.consumeFuel();
    EXPECT_EQ(mediumairplane.getFuel(), 75);
    mediumairplane.setStatus("Refueling Plane");
    mediumairplane.refuelPlane(stream);
    mediumairplane.refuelPlane(stream);
    EXPECT_EQ(mediumairplane.getFuel(), 20075);
    largeairplane.setFuel(250); // Test large propeller
    largeairplane.setEngine("propeller");
    largeairplane.consumeFuel();
    EXPECT_EQ(largeairplane.getFuel(), 150);
    largeairplane.setStatus("Refueling Plane");
    largeairplane.refuelPlane(stream);
    largeairplane.refuelPlane(stream);
    EXPECT_EQ(largeairplane.getFuel(), 20150);
    largeairplane.setFuel(250); // Test large jet
    largeairplane.setEngine("jet");
    largeairplane.consumeFuel();
    EXPECT_EQ(largeairplane.getFuel(), 0);
    largeairplane.setStatus("Refueling Plane");
    largeairplane.refuelPlane(stream);
    largeairplane.refuelPlane(stream);
    EXPECT_EQ(largeairplane.getFuel(), 20000);
}
