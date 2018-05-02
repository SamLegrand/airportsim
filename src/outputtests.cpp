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
    Exporter exporter;
};

TEST_F(AirportSimOutputTest, OutputSimpleScenario){     //Testing output for simple scenario (only two planes plane)
    AirportSim simulator("../testOutput/airleadersimplescenario.txt");
    //Make sure testInput directory exists, if not, no need to continue with test
    ASSERT_TRUE(DirectoryExists("../testInput/"));
    ASSERT_TRUE(DirectoryExists("../testOutput/"));

    std::ofstream filestream;
    std::ofstream errstream;
    importer::importAirport("../testInput/inputlegal.xml", errstream, simulator);

    //Test graphical impression
    filestream.open("../testOutput/simplescenariographicalimpression.txt");
    exporter.exportGraphicalImpression(filestream, simulator.getAirports());
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/simplescenariographicalimpressionexpected.txt", "../testOutput/simplescenariographicalimpression.txt"));

    //Test simulation output
    filestream.open("../testOutput/simplescenario.txt");
    simulator.simulate(filestream);
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/simplescenarioexpected.txt", "../testOutput/simplescenario.txt"));

    //Test for correct airleader output
    EXPECT_TRUE(FileCompare("../testOutput/airleadersimplescenario.txt", "../testOutput/airleadersimplescenarioexpected.txt"));

    //Test simple output
    filestream.open("../testOutput/simplescenariosimpleoutput.txt");
    exporter.exportSimpleOutput(filestream, simulator.getAirports(), simulator.getAirplanes());
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/simplescenariosimpleoutputexpected.txt", "../testOutput/simplescenariosimpleoutput.txt"));
}

TEST_F(AirportSimOutputTest, OutputComplexScenario){    //Testing correct output for more complex scenario (multiple planes in different states)
    AirportSim simulator("../testOutput/airleadercomplexscenario.txt");
    //Make sure testInput directory exists, if not, no need to continue with test
    ASSERT_TRUE(DirectoryExists("../testInput/"));
    ASSERT_TRUE(DirectoryExists("../testOutput/"));

    std::ofstream filestream;
    std::ofstream errstream;
    importer::importAirport("../testInput/inputlegalcomplex.xml", errstream, simulator);

    //Test graphical impression
    filestream.open("../testOutput/complexscenariographicalimpression.txt");
    exporter.exportGraphicalImpression(filestream, simulator.getAirports());
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/complexscenariographicalimpressionexpected.txt", "../testOutput/complexscenariographicalimpression.txt"));

    //Test simulation output
    filestream.open("../testOutput/complexscenario.txt");
    simulator.simulate(filestream);
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/complexscenarioexpected.txt", "../testOutput/complexscenario.txt"));

    //Test for correct airleader output
    EXPECT_TRUE(FileCompare("../testOutput/airleadercomplexscenarioexpected.txt", "../testOutput/airleadercomplexscenario.txt"));

    //Test simple output
    filestream.open("../testOutput/complexscenariosimpleoutput.txt");
    exporter.exportSimpleOutput(filestream, simulator.getAirports(), simulator.getAirplanes());
    filestream.close();
    EXPECT_TRUE(FileCompare("../testOutput/complexscenariosimpleoutputexpected.txt", "../testOutput/complexscenariosimpleoutput.txt"));
}
