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
    simulation.simulate(cout);      //Simulate airport
    return 0;
}
