//
// Created by lena on 3/16/18.
//

#ifndef AIRPORTSIM_AIRPORTSIM_H
#define AIRPORTSIM_AIRPORTSIM_H


#include "airport.h"

class AirportSim {
    AirportSim* initCheck;
    std::vector<Airport*> airports;
    std::vector<Airplane*> airplanes;
    std::string airleaderoutput;
public:
    /**
     * ENSURE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
     */
    AirportSim();
    /**
     * ENSURE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
     * @param airleaderoutput
     */
    AirportSim(const std::string &airleaderoutput);
    /**
     *
     * @return
     */
    bool properlyInitialized();

    /**
     * REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
     * @return
     */
    const std::vector<Airport *> &getAirports();
    /**
     * REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
     * @param airports
     */
    void setAirports(const std::vector<Airport *> &airports);

    /**
     * REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
     * @return
     */
    const std::vector<Airplane *> &getAirplanes();
    /**
     * REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
     * @param airplanes
     */
    void setAirplanes(const std::vector<Airplane *> &airplanes);

    const std::string &getAirleaderoutput() const;

    void setAirleaderoutput(const std::string &airleaderoutput);

    /**
     * REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
     * @param output
     */
    void simulate(std::ostream &output);
    /**
     * REQUIRE(this->properlyInitialized(), "Simulation wasn't properly initialized.");
     * @return
     */
    bool checkSimEnd();

    void useGraphicsExporter(int &filecounter, Exporter &exporter, bool use);

    bool handleEmergency(Airplane* airplane, Exporter &exporter, Airport* airport, const int &SimTime, std::ostream &output);

    void airplaneExcecute(Airplane* airplane, Airport* airport, Exporter& exporter, unsigned int &time, std::ostream &SimOutput);
};


#endif //AIRPORTSIM_AIRPORTSIM_H
