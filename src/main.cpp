#include <iostream>
#include <sstream>
#include "importer.h"

using namespace std;

int main() {
    AirportSim simulation;
    ofstream myfile;
    myfile.open("error.txt");
    importer::importAirport("../input.xml", myfile, simulation);
    myfile.close();
    simulation.simulate(cout);
    return 0;
}
