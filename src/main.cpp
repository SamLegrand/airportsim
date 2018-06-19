#include <iostream>
#include <sstream>
#include "importer.h"
#include "Exporter.h"

using namespace std;

int main() {
    AirportSim simulation;      //Create simulation
    ofstream myfile;        //Create filestream
    myfile.open("error.txt");
    importer::importAirport("../testInput/inputlegalcomplex1.xml", myfile, simulation);        //Import from xml file
    myfile.close();
    myfile.open("../EngineTest.ini");
    Exporter* exporter = new Exporter();
    exporter->exportIni(myfile, simulation.getAirports());
    myfile.close();
    simulation.simulate(cout);      //Simulate airport
    return 0;
}
