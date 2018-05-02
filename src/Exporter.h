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
    std::ofstream airleaderOutput;
public:
    Exporter();
    Exporter(const std::string &filename);
    bool properlyInitizalized();
    void exportSimpleOutput(std::ofstream &output, const std::vector<Airport*> &airports, const std::vector<Airplane*> &airplanes);
    void exportGraphicalImpression(std::ofstream &output, const std::vector<Airport*> &airports);
    void exportIni(std::ofstream &output, const std::vector<Airport*> &airports);
    void generateImg(std::string filename);
    void printAirleaderMessage(int time, std::string source, std::string message);
    void closeAirleaderOutput();
};

#endif //AIRPORTSIM_EXPORTER_H
