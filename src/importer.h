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
    static void writeGraphicalOutput(const std::vector<Airport*> &airports, std::ofstream &output);
    static bool properlyInitialized(const std::vector<Airport*> &airports, const std::vector<Runway*> runwaysNotAddedToPlane, const std::vector<Airplane*> &airplanes);
};


#endif //AIRPORTSIM_IMPORTER_H
