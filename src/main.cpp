#include <iostream>
#include <sstream>
#include "importer.h"

using namespace std;

int main() {
    AirportSim simulation;      //Create simulation
    ofstream myfile;        //Create filestream
    myfile.open("error.txt");
    importer::importAirport("../input_system2.xml", myfile, simulation);        //Import from xml file
    myfile.close();
    myfile.open("../EngineTest.ini");
    simulation.writeEngineIni();
    myfile.close();
    simulation.simulate(cout);      //Simulate airport
    return 0;
}
