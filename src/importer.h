//
// Created by sam on 16.03.18.
//

#ifndef AIRPORTSIM_IMPORTER_H
#define AIRPORTSIM_IMPORTER_H

#include <iostream>
#include <sys/param.h>
#include "AirportSim.h"

enum SuccessEnum {ImportAborted, PartialImport, Success};

class importer {
private:
    importer* initCheck;
public:
    static SuccessEnum importAirport(const char* inputfilename, std::ostream& errstream, AirportSim& simulation);
    static int namesAreUnique(const std::vector<Airport*> &airports, const std::vector<Airplane*> &airplanes);
    static bool setSquawkCodes(const std::vector<Airplane*> &airplanes);
    static bool enoughTaxipoints(const std::vector<Airport*> &airports);
    static bool planesCanLand(const std::vector<Airport*> &airports, const std::vector<Airplane*> &airplanes);
    static bool correctCrossings(const std::vector<Airport*> &airports, const std::vector<std::string> &crossings);
};


#endif //AIRPORTSIM_IMPORTER_H
