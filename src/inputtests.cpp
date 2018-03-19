//
// Created by sam on 16.03.18.
//

#include <iostream>
#include <gtest/gtest.h>

#include "AirportSim.h"
#include "importer.h"
#include "utils.h"

class AirportSimInputTest: public ::testing::Test {
protected:
    virtual void SetUp(){

    }
    virtual void TearDown(){

    }
    AirportSim simulator;
    Airplane airplane_;
    Airport airport_;
    Runway runway_;

    TEST_F(AirportSimInputTest, InputCorrect){
        ofstream filestream;
        SuccessEnum result;

        filestream.open("testInput/Error.txt");
        result = importer::importAirport("../input.xml", filestream, simulator);
        filestream.close();
        EXPECT_TRUE(result == Success);
    }

    TEST_F(AirportSimInputTest, InputXMLSyntaxErrors){
        ofstream filestream;
        SuccessEnum  result;
        int counter = 1;
        string fileName = "testInput/inputsyntaxerror" + to_string(counter) + ".xml";

        filestream.open("testInput/Error.txt");
        result = importer::importAirport("../inputsyntaxerror.xml", filestream, simulator);
        filestream.close();
        EXPECT_TRUE(result == ImportAborted);
    }
};
