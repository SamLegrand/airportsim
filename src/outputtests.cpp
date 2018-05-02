//
// Created by sam on 16.03.18.
//

#include <iostream>
#include <gtest/gtest.h>

#include "AirportSim.h"
#include "importer.h"
#include "utils.h"
#include "Exporter.h"

class AirportSimOutputTest: public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
};

TEST_F(AirportSimOutputTest, OutputSimpleScenario){     //Testing output for simple scenario (only one plane)
    AirportSim simulator("../testOutput/airleadersimplescenario.txt");
    std::ofstream filestream;
    std::ofstream errstream;
    Exporter exporter;
    importer::importAirport("../testInput/inputlegal.xml", errstream, simulator);
    filestream.open("../testOutput/simplescenariographicalimpression.txt");
    exporter.exportGraphicalImpression(filestream, simulator.getAirports());
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/simplescenariographicalimpressionexpected.txt", "../testOutput/simplescenariographicalimpression.txt"));
    filestream.open("../testOutput/simplescenario.txt");
    simulator.simulate(filestream);
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/simplescenarioexpected.txt", "../testOutput/simplescenario.txt"));
    EXPECT_TRUE(FileCompare("../testOutput/airleadersimplescenario.txt", "../testOutput/airleadersimplescenarioexpected.txt"));
    filestream.open("../testOutput/simplescenariosimpleoutput.txt");
    exporter.exportSimpleOutput(filestream, simulator.getAirports(), simulator.getAirplanes());
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/simplescenariosimpleoutputexpected.txt", "../testOutput/simplescenariosimpleoutput.txt"));
}

TEST_F(AirportSimOutputTest, OutputComplexScenario){    //Testing correct output for more complex scenario (multiple planes in different states)
    AirportSim simulator("../testOutput/airleadercomplexscenario.txt");
    std::ofstream filestream;
    std::ofstream errstream;
    Exporter exporter;
    importer::importAirport("../testInput/inputlegalcomplex.xml", errstream, simulator);
    filestream.open("../testOutput/complexscenariographicalimpression.txt");
    exporter.exportGraphicalImpression(filestream, simulator.getAirports());
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/complexscenariographicalimpressionexpected.txt", "../testOutput/complexscenariographicalimpression.txt"));
    filestream.open("../testOutput/complexscenario.txt");
    simulator.simulate(filestream);
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/complexscenarioexpected.txt", "../testOutput/complexscenario.txt"));
    EXPECT_TRUE(FileCompare("../testOutput/airleadercomplexscenarioexpected.txt", "../testOutput/airleadercomplexscenario.txt"));
    filestream.open("../testOutput/complexscenariosimpleoutput.txt");
    exporter.exportSimpleOutput(filestream, simulator.getAirports(), simulator.getAirplanes());
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/complexscenariosimpleoutputexpected.txt", "../testOutput/complexscenariosimpleoutput.txt"));
}
