//
// Created by sam on 16.03.18.
//

#include <iostream>
#include <gtest/gtest.h>

#include "AirportSim.h"
#include "importer.h"

class AirportSimInputTest: public ::testing::Test {
protected:
    virtual void SetUp(){

    }
    virtual void TearDown(){

    }
    Airplane airplane_;
    Airport airport_;
    Runway runway_;
};
