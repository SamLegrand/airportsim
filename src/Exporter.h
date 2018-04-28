//
// Created by sam on 28.04.18.
//

#ifndef AIRPORTSIM_EXPORTER_H
#define AIRPORTSIM_EXPORTER_H


#include <fstream>
#include "airport.h"

class Exporter {
private:
    Exporter* initCheck;
    bool docStarted;
public:
    Exporter();
    bool properlyInitizalized();
    bool documentStarted();
    virtual void documentStart(std::ofstream &output);
    virtual void documentEnd(std::ofstream &output);
    void exportGraphicalImpression(std::ofstream &output, const std::vector<Airport*> &airports);
};

class EngineIniExporter: public Exporter {
public:
    void exportIni(std::ofstream &output, const std::vector<Airport*> &airports);
};

class AirleaderExporter: public Exporter {
public:
    void printMessage(std::ofstream &output, int time, std::string source, std::string message);
};


#endif //AIRPORTSIM_EXPORTER_H
