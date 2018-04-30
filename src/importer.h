//
// Created by sam on 16.03.18.
//

#ifndef AIRPORTSIM_IMPORTER_H
#define AIRPORTSIM_IMPORTER_H

#include <iostream>
#include "AirportSim.h"

enum SuccessEnum {ImportAborted, PartialImport, Success};

class importer {
private:
    importer* initCheck;
public:
    static SuccessEnum importAirport(const char* inputfilename, std::ostream& errstream, AirportSim& simulation);
    static bool properlyInitialized(const std::vector<Airport*> &airports, const std::vector<std::string> &crossings, const std::vector<Runway*> runwaysNotAddedToPlane, const std::vector<Airplane*> &airplanes);
};


#endif //AIRPORTSIM_IMPORTER_H
