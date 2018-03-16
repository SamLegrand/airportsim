//
// Created by sam on 16.03.18.
//

#ifndef AIRPORTSIM_IMPORTER_H
#define AIRPORTSIM_IMPORTER_H

#include <iostream>

enum SuccessEnum {ImportAborted, PartialImport, Success};

class importer {
public:
    static SuccesEnum importAirport(const char* inputfilename, std::ostream& errstream, airportsim& simulation);
};


#endif //AIRPORTSIM_IMPORTER_H
