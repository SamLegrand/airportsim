//
// Created by sam on 15.03.18.
//

#include <iostream>
#include <gtest/gtest.h>
#include "airplane.h"
#include "airport.h"
#include "runway.h"

class AirportSimTest: public ::testing::Test {
protected:
    virtual void SetUp(){

    }
    virtual void TearDown(){

    }
    Airplane airplane_;
    Airport airport_;
    Runway runway_;
};

TEST_F(AirportSimTest, AirplaneFunctions){
    airplane_.setNumber("N11842");
    airplane_.setCallsign("Cessna 842");
    airplane_.setModel("Cessna 340");
    airplane_.setStatus("Approaching");
    airplane_.setPassengers(60);
    airplane_.setFuel(20);
    testing::internal::CaptureStdout();
    airplane_.approach("Antwerp International Airport");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Cessna 842 is approaching Antwerp International Airport at 10000 ft.\n");
    EXPECT_EQ(10000, airplane_.getHeight());
    testing::internal::CaptureStdout();
    airplane_.descend();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Cessna 842 descended to 9000 ft.\n");
    EXPECT_EQ(9000, airplane_.getHeight());
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}