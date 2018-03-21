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
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

    AirportSim simulator;
};

TEST_F(AirportSimInputTest, InputLegal){
    ofstream filestream;
    SuccessEnum  result;

    filestream.open("../testInput/Error.txt");
    result = importer::importAirport("../testInput/inputlegal.xml", filestream, simulator);
    filestream.close();
    EXPECT_TRUE(result == Success);
    EXPECT_TRUE(FileIsEmpty("../testInput/Error.txt"));
}

TEST_F(AirportSimInputTest, InputSyntaxErrors){
    ofstream filestream;
    SuccessEnum  result;
    int counter = 1;
    string filename = "../testInput/inputsyntaxerror" + to_string(counter) + ".xml";
    string errorfilename;

    while(FileExists(filename)){
        filestream.open("../testInput/Error.txt");
        result = importer::importAirport(filename.c_str(), filestream, simulator);
        filestream.close();
        EXPECT_TRUE(result == ImportAborted);
        errorfilename = "../testInput/inputsyntaxerror" + to_string(counter) + ".txt";
        EXPECT_TRUE(FileCompare("../testInput/Error.txt", errorfilename));

        counter++;
        filename = "../testInput/inputsyntaxerror" + to_string(counter) + ".xml";
    };

    EXPECT_TRUE(counter == 5);
}

TEST_F(AirportSimInputTest, InputIllegal){
    ASSERT_TRUE(DirectoryExists("../testInput"));

    ofstream filestream;
    SuccessEnum  result;
    int counter = 1;
    string filename = "../testInput/inputillegal" + to_string(counter) + ".xml";
    string errorfilename;

    while(FileExists(filename)){
        filestream.open("../testInput/Error.txt");
        result = importer::importAirport(filename.c_str(), filestream, simulator);
        filestream.close();
        EXPECT_TRUE(result == PartialImport);
        errorfilename = "../testInput/inputillegal" + to_string(counter) + ".txt";
        EXPECT_TRUE(FileCompare("../testInput/Error.txt", errorfilename));

        counter++;
        filename = "../testInput/inputillegal" + to_string(counter) + ".xml";
    };

    EXPECT_TRUE(counter == 5);
}
