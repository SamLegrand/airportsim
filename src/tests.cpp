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

TEST_F(AirportSimTest, TakeOff){
    
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}