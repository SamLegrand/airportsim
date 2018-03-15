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

TEST_F(AirportSimTest, AirplaneGettersSetters){
    airplane_.setNumber("N11842");
    airplane_.setCallsign("Cessna 842");
    airplane_.setModel("Cessna 340");
    airplane_.setStatus("Approaching");
    airplane_.setPassengers(60);
    airplane_.setFuel(20);
    airplane_.setHeight(5000);
    EXPECT_EQ("N11842", airplane_.getNumber());
    EXPECT_EQ("Cessna 842", airplane_.getCallsign());
    EXPECT_EQ("Cessna 340", airplane_.getModel());
    EXPECT_EQ("Approaching", airplane_.getStatus());
    EXPECT_EQ(60, airplane_.getPassengers());
    EXPECT_EQ(20, airplane_.getFuel());
    EXPECT_EQ(5000, airplane_.getHeight());
}

TEST_F(AirportSimTest, AirplaneFunctions){
    
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}