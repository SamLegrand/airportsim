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
    /**
     * ENSURE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
     */
    Exporter();
    /**
     * ENSURE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
     * @param filename
     */
    Exporter(const std::string &filename);
    /**
     *
     * @return
     */
    bool properlyInitialized();
    /**
     * REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
     * @param output
     * @param airports
     * @param airplanes
     */
    void exportSimpleOutput(std::ofstream &output, const std::vector<Airport*> &airports, const std::vector<Airplane*> &airplanes);
    /**
     * REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
     * @param output
     * @param airports
     */
    void exportGraphicalImpression(std::ofstream &output, const std::vector<Airport*> &airports);
    /**
     * REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
     * @param output
     * @param airports
     */
    void exportIni(std::ofstream &output, const std::vector<Airport*> &airports);
    /**
     * REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
     * @param filename
     */
    void generateImg(std::string filename);
    /**
     * REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
     * @param time
     * @param source
     * @param message
     */
    void printAirleaderMessage(int time, std::string source, std::string message);
    /**
     * REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
     */
    void closeAirleaderOutput();
};

#endif //AIRPORTSIM_EXPORTER_H
