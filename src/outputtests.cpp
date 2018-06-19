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
    AirportSim simulator;
    //Make sure testInput directory exists, if not, no need to continue with test
    ASSERT_TRUE(DirectoryExists("../testInput/"));
    ASSERT_TRUE(DirectoryExists("../testOutput/"));

    std::ofstream filestream;
    std::ofstream errstream;
    ASSERT_TRUE(DirectoryExists("../testInput/"));
    int counter = 1;        //Counter for looping over different files
    std::string filename = "../testInput/inputlegal" + to_string(counter) + ".xml";

    while(FileExists(filename)){        //Loop over different files
        importer::importAirport(filename.c_str(), errstream, simulator);

        //Test graphical impression
        std::string output = "../testOutput/simplescenario" + to_string(counter) + "graphicalimpression.txt";
        filestream.open(output.c_str());
        exporter.exportGraphicalImpression(filestream, simulator.getAirports());
        filestream.close();
        EXPECT_TRUE(FileCompare("../testOutput/simplescenario" + to_string(counter) + "graphicalimpressionexpected.txt", "../testOutput/simplescenario" + to_string(counter) + "graphicalimpression.txt"));

        //Test simulation output
        output = "../testOutput/simplescenario" + to_string(counter) + ".txt";
        filestream.open(output.c_str());
        simulator.simulate(filestream);
        filestream.close();
        EXPECT_TRUE(FileCompare("../testOutput/simplescenario" + to_string(counter) + "expected.txt", "../testOutput/simplescenario" + to_string(counter) + ".txt"));

        //Test simple output
        output = "../testOutput/simplescenario" + to_string(counter) + "simpleoutput.txt";
        filestream.open(output.c_str());
        exporter.exportSimpleOutput(filestream, simulator.getAirports(), simulator.getAirplanes());
        filestream.close();
        EXPECT_TRUE(FileCompare("../testOutput/simplescenario" + to_string(counter) + "simpleoutputexpected.txt", "../testOutput/simplescenario" + to_string(counter) + "simpleoutput.txt"));

        counter++;
        filename = "../testInput/inputlegal" + to_string(counter) + ".xml";
    };

    EXPECT_TRUE(counter == 4);      //Expect that all files have been tested
}

TEST_F(AirportSimOutputTest, OutputComplexScenarios){    //Testing correct output for more complex scenario (multiple planes in different states)
    AirportSim simulator;
    //Make sure testInput directory exists, if not, no need to continue with test
    ASSERT_TRUE(DirectoryExists("../testInput/"));
    ASSERT_TRUE(DirectoryExists("../testOutput/"));

    std::ofstream filestream;
    std::ofstream errstream;
    ASSERT_TRUE(DirectoryExists("../testInput/"));
    int counter = 1;        //Counter for looping over different files
    std::string filename = "../testInput/inputlegalcomplex" + to_string(counter) + ".xml";

    while(FileExists(filename)){        //Loop over different files
        importer::importAirport(filename.c_str(), errstream, simulator);

        //Test graphical impression
        std::string output = "../testOutput/complexscenario" + to_string(counter) + "graphicalimpression.txt";
        filestream.open(output.c_str());
        exporter.exportGraphicalImpression(filestream, simulator.getAirports());
        filestream.close();
        EXPECT_TRUE(FileCompare("../testOutput/complexscenario" + to_string(counter) + "graphicalimpressionexpected.txt", "../testOutput/complexscenario" + to_string(counter) + "graphicalimpression.txt"));

        //Test simulation output
        output = "../testOutput/complexscenario" + to_string(counter) + ".txt";
        filestream.open(output.c_str());
        simulator.simulate(filestream);
        filestream.close();
        EXPECT_TRUE(FileCompare("../testOutput/complexscenario" + to_string(counter) + "expected.txt", "../testOutput/complexscenario" + to_string(counter) + ".txt"));

        //Test simple output
        output = "../testOutput/complexscenario" + to_string(counter) + "simpleoutput.txt";
        filestream.open(output.c_str());
        exporter.exportSimpleOutput(filestream, simulator.getAirports(), simulator.getAirplanes());
        filestream.close();
        EXPECT_TRUE(FileCompare("../testOutput/complexscenario" + to_string(counter) + "simpleoutputexpected.txt", "../testOutput/complexscenario" + to_string(counter) + "simpleoutput.txt"));

        counter++;
        filename = "../testInput/inputlegalcomplex" + to_string(counter) + ".xml";
    };

    EXPECT_TRUE(counter == 4);      //Expect that all files have been tested
}
