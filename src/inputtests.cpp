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

TEST_F(AirportSimInputTest, InputLegal){         //Testing correct import for legal input
    std::ofstream filestream;
    SuccessEnum  result;

    filestream.open("../testInput/Error.txt");
    result = importer::importAirport("../testInput/inputlegal.xml", filestream, simulator);
    filestream.close();
    EXPECT_TRUE(result == Success);     //Input is expected to be imported successfully
    EXPECT_TRUE(FileIsEmpty("../testInput/Error.txt"));     //It's expected that no errors will occur
}

//TEST_F(AirportSimInputTest, InputLegalComplex){         //Testing correct import for legal input (more complex)
//    std::ofstream filestream;
//    SuccessEnum  result;
//
//    filestream.open("../testInput/Error.txt");
//    result = importer::importAirport("../testInput/inputlegalcomplex.xml", filestream, simulator);
//    filestream.close();
//    EXPECT_TRUE(result == Success);     //Input is expected to be imported successfully
//    EXPECT_TRUE(FileIsEmpty("../testInput/Error.txt"));     //It's expected that no errors will occur
//}

TEST_F(AirportSimInputTest, InputSyntaxErrors){     //Testing errors in syntax
    std::ofstream filestream;
    SuccessEnum  result;
    int counter = 1;        //Counter for looping over different files
    std::string filename = "../testInput/inputsyntaxerror" + to_string(counter) + ".xml";
    std::string errorfilename;

    while(FileExists(filename)){        //Loop over different files
        filestream.open("../testInput/Error.txt");
        result = importer::importAirport(filename.c_str(), filestream, simulator);
        filestream.close();
        EXPECT_TRUE(result == ImportAborted);       //Import should be aborted
        errorfilename = "../testInput/inputsyntaxerror" + to_string(counter) + ".txt";
        EXPECT_TRUE(FileCompare("../testInput/Error.txt", errorfilename));      //Compare error output with the expected error output

        counter++;
        filename = "../testInput/inputsyntaxerror" + to_string(counter) + ".xml";
    };

    EXPECT_TRUE(counter == 5);      //Expect that all files have been tested
}

TEST_F(AirportSimInputTest, InputIllegal){      //Testing illegal input
    ASSERT_TRUE(DirectoryExists("../testInput"));

    std::ofstream filestream;
    SuccessEnum  result;
    int counter = 1;        //Counter for looping over different files
    std::string filename = "../testInput/inputillegal" + to_string(counter) + ".xml";
    std::string errorfilename;

    while(FileExists(filename)){        //Loop over different files
        filestream.open("../testInput/Error.txt");
        result = importer::importAirport(filename.c_str(), filestream, simulator);
        filestream.close();
        EXPECT_TRUE(result == PartialImport);       //Input should be partially imported
        errorfilename = "../testInput/inputillegal" + to_string(counter) + ".txt";
        EXPECT_TRUE(FileCompare("../testInput/Error.txt", errorfilename));      //Compare error output with the expected error output

        counter++;
        filename = "../testInput/inputillegal" + to_string(counter) + ".xml";
    };

    EXPECT_TRUE(counter == 5);      //Expect that all files have been tested
}

TEST_F(AirportSimInputTest, InputNoPlaneWithType){        //Testing correct import for legal input
    std::ofstream filestream;
    SuccessEnum  result;

    filestream.open("../testInput/Error.txt");
    result = importer::importAirport("../testInput/inputnotype.xml", filestream, simulator);
    filestream.close();
    EXPECT_TRUE(result == PartialImport);     //Input is expected to be imported successfully
    EXPECT_TRUE(FileCompare("../testInput/Error.txt", "../testInput/inputnotypeerror.txt"));     //It's expected that no errors will occur
}
