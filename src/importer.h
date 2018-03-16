//
// Created by sam on 16.03.18.
//

#ifndef AIRPORTSIM_IMPORTER_H
#define AIRPORTSIM_IMPORTER_H

#include <iostream>
#include "AirportSim.h"

enum SuccessEnum {ImportAborted, PartialImport, Success};

class importer {
public:
    static SuccessEnum importAirport(const char* inputfilename, std::ostream& errstream, AirportSim& simulation);
};


#endif //AIRPORTSIM_IMPORTER_H
