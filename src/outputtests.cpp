//
// Created by sam on 16.03.18.
//

#include <iostream>
#include <gtest/gtest.h>

#include "AirportSim.h"
#include "importer.h"
#include "utils.h"

class AirportSimOutputTest: public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

    AirportSim simulator;
};

TEST_F(AirportSimOutputTest, OutputSimpleScenario){     //Testing output for simple scenario (only one plane)
    ofstream filestream;
    ofstream errstream;
    filestream.open("../testOutput/simplescenario.txt");
    importer::importAirport("../testInput/inputlegal.xml", errstream, simulator);
    simulator.simulate(filestream);
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/simplescenarioexpected.txt", "../testOutput/simplescenario.txt"));
}

TEST_F(AirportSimOutputTest, OutputComplexScenario){    //Testing correct output for more complex scenario (multiple planes in different states)
    ofstream filestream;
    ofstream errstream;
    filestream.open("../testOutput/complexscenario.txt");
    importer::importAirport("../testInput/inputlegalcomplex.xml", errstream, simulator);
    simulator.simulate(filestream);
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/complexscenarioexpected.txt", "../testOutput/complexscenario.txt"));
}