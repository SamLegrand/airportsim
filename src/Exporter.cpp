//
// Created by sam on 28.04.18.
//

#include <sstream>
#include <cstdlib>
#include "Exporter.h"
#include "utils.h"

Exporter::Exporter() {
    initCheck = this;
    airleaderOutput.open("../AirControlOutput.txt");
    ENSURE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
}

Exporter::Exporter(const std::string &filename){
    initCheck = this;
    airleaderOutput.open(filename.c_str());
    ENSURE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
}

bool Exporter::properlyInitialized() {
    return initCheck == this;
}

void Exporter::exportSimpleOutput(std::ofstream &output, const std::vector<Airport*> &airports, const std::vector<Airplane*> &airplanes){
    REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
    for (unsigned int i = 0; i < airports.size(); ++i) {
        airports[i]->printInfo(output);
    }
    for (unsigned int i=0; i< airplanes.size(); ++i) {
        airplanes[i]->printInfo(output);
    }
}

void Exporter::exportGraphicalImpression(std::ofstream &output, const std::vector<Airport*> &airports){
    REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
    for (unsigned int i = 0; i < airports.size(); ++i) {
        airports[i]->sortRunways();
        for (unsigned int j = 0; j < airports[i]->getRunways().size(); ++j) {
            output << airports[i]->getRunways()[j]->getName() << " | ";
            if (airports[i]->getRunways()[j]->getAirplane()){
                output << "====V=====" << std::endl;
            }
            else{
                output << "==========" << std::endl;
            }
            output << "TP" << airports[i]->getRunways()[j]->getTaxipoint()[0] << " | " << std::endl;
        }
        output << "Gates [";
        for (int j = 0; j < airports[i]->getGates(); ++j) {
            if(airports[i]->getGatesVector()[j]){
                output << "V";
            }
            else{
                output << " ";
            }
        }
        output << "]" << std::endl << std::endl;
    }
}

void Exporter::exportIni(std::ofstream &output, const std::vector<Airport *> &airports){
    REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
    std::string initinfo = "[General]\n"
            "size = 1024\n"
            "backgroundcolor = (0, 0.749, 1)\n"
            "type = \"LightedZBuffering\"\n"
            "nrLights = 1\n"
            "eye = (-100, 0, 75)\n";
    std::string cubeinfo = "type = \"Cube\"\n"
            "scale = 1\n"
            "rotateX = 0\n"
            "rotateY = 0\n"
            "rotateZ = 0\n";
    std::string coneinfo = "type = \"Cone\"\n"
            "height = 5\n"
            "n = 360\n"
            "scale = 0.25\n";
    std::string buckyballinfo = "type = \"BuckyBall\"\n"
            "scale = 0.25\n"
            "rotateX = 0\n"
            "rotateY = 0\n"
            "rotateZ = 0\n";
    std::string cylinderinfo = "type = \"Cylinder\"\n"
            "height = 3.5\n"
            "scale = 0.10\n"
            "rotateX = -90\n"
            "rotateY = 0\n"
            "rotateZ = 0\n"
            "n = 30\n";
    std::string reflectionrunway = "ambientReflection = (0.00, 0.50, 0.00)\n"
            "diffuseReflection = (0.00, 0.50, 0.00)\n"
            "specularReflection = (0.4, 0.4, 0.4)\n"
            "reflectionCoefficient = 20\n";
    std::string reflectiontaxipoint = "ambientReflection = (0.00, 0.00, 0.50)\n"
            "diffuseReflection = (0.00, 0.00, 0.50)\n"
            "specularReflection = (0.4, 0.4, 0.4)\n"
            "reflectionCoefficient = 20\n";
    std::string reflectiongate = "ambientReflection = (0.50, 0.50, 0.00)\n"
            "diffuseReflection = (0.50, 0.50, 0.00)\n"
            "specularReflection = (0.4, 0.4, 0.4)\n"
            "reflectionCoefficient = 20\n";
    std::string reflectionairplane = "ambientReflection = (0.50, 0.00, 0.00)\n"
            "diffuseReflection = (0.50, 0.00, 0.00)\n"
            "specularReflection = (0.4, 0.4, 0.4)\n"
            "reflectionCoefficient = 20\n";
    std::string reflectiondome = "ambientReflection = (0.00, 0.25, 0.50)\n"
            "diffuseReflection = (0.00, 0.25, 0.50)\n"
            "specularReflection = (0.4, 0.4, 0.4)\n"
            "reflectionCoefficient = 20\n";
    std::string light = "[Light0]\n"
            "infinity = TRUE\n"
            "direction = (-1, -1, -1)\n"
            "ambientLight = (1, 1, 1)\n"
            "diffuseLight = (1, 1, 1)\n"
            "specularLight = (1, 1, 1)\n";
    std::string airplaneoccupied = "rotateX = -90\n"
            "rotateY = 0\n"
            "rotateZ = 0\n"
            "center = (0, -0.5, 1)\n";
    std::string airplanestanding = "rotateX = -90\n"
            "rotateY = 0\n"
            "rotateZ = 0\n";
    std::string airplanetogate = "rotateX = 0\n"
            "rotateY = -90\n"
            "rotateZ = 0\n";
    std::string airplanetorunway = "rotateX = 0\n"
            "rotateY = 90\n"
            "rotateZ = 0\n";
    std::string airplanelanding = "rotateX = 110\n"
            "rotateY = 0\n"
            "rotateZ = 0\n";
    std::string airplanetakingoff = "rotateX = -70\n"
            "rotateY = 0\n"
            "rotateZ = 0\n";

    //Write to ini
    for (unsigned int i = 0; i < airports.size(); ++i) {
        std::stringstream figureinfo;
        figureinfo << light << std::endl;
        int gatesoffset = airports[i]->getRunways().size();
        int figNum = 0;
        figureinfo << "[Figure" << figNum << "]\n" << cubeinfo << "center = (" << 0 << ", 0, 0)\n" << reflectionrunway << std::endl;
        figureinfo << "[Figure" << figNum + 1 << "]\n" << cubeinfo << "center = (" << 0 << ", 2, 0)\n" << reflectionrunway << std::endl;
        figureinfo << "[Figure" << figNum + 2 << "]\n" << cubeinfo << "center = (" << 0 << ", 4, 0)\n" << reflectionrunway << std::endl;
        figNum += 3;
//        if (airports[i]->getFarthestRunway()->getAirplane() != NULL){
//            if (airports[i]->getFarthestRunway()->getAirplane()->isAtRunway()){
//                figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanestanding << "center = (" << 0 << ", -0.5, 1)\n" << reflectionairplane << std::endl;
//                figNum += 1;
//            }
//            else if(airports[i]->getFarthestRunway()->getAirplane()->getStatus() == "Landing"){
//                figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanelanding << "center = (" << 0 << ", 6, 2)\n" << reflectionairplane << std::endl;
//                figNum += 1;
//            }
//            else if(airports[i]->getFarthestRunway()->getAirplane()->getStatus() == "Taking Off"){
//                figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetakingoff << "center = (" << 0 << ", 2, 2)\n" << reflectionairplane << std::endl;
//                figNum += 1;
//            }
//            else if(airports[i]->getFarthestRunway()->getAirplane()->getStatus() == "Ascending"){
//                figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetakingoff << "center = (" << 0 << ", 4, 3)\n" << reflectionairplane << std::endl;
//                figNum += 1;
//            }
//        }
        for (unsigned int j = 0; j < airports[i]->getRunways().size(); ++j) {
            figureinfo << "[Figure" << figNum << "]\n" << cubeinfo << "center = (" << -4*(int)j << ", 0, 0)\n" << reflectionrunway << std::endl;
            figureinfo << "[Figure" << figNum + 1 << "]\n" << cubeinfo << "center = (" << -4*(int)j << ", 2, 0)\n" << reflectionrunway << std::endl;
            figureinfo << "[Figure" << figNum + 2 << "]\n" << cubeinfo << "center = (" << -4*(int)j << ", 4, 0)\n" << reflectionrunway << std::endl;
            figNum += 3;
            if (airports[i]->getRunways()[j]->getAirplane() != NULL){
                if (airports[i]->getRunways()[j]->getAirplane()->isAtRunway()){
                    figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanestanding << "center = (" << -4*(int)j << ", -0.5, 1)\n" << reflectionairplane << std::endl;
                    figNum += 1;
                }
                else if(airports[i]->getRunways()[j]->getAirplane()->getStatus() == "Landing"){
                    figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanelanding << "center = (" << -4*(int)j << ", 6, 2)\n" << reflectionairplane << std::endl;
                    figNum += 1;
                }
                else if(airports[i]->getRunways()[j]->getAirplane()->getStatus() == "Taking Off"){
                    figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetakingoff << "center = (" << -4*(int)j << ", 2, 2)\n" << reflectionairplane << std::endl;
                    figNum += 1;
                }
                else if(airports[i]->getRunways()[j]->getAirplane()->getStatus() == "Ascending"){
                    figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetakingoff << "center = (" << -4*(int)j << ", 4, 3)\n" << reflectionairplane << std::endl;
                    figNum += 1;
                }
            }
            if (airports[i]->getRunways()[j]->getAirplaneCrossing() != NULL){
                if (airports[i]->getRunways()[j]->getAirplaneCrossing()->getStatus() == "Crossing to Runway"){
                    figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetorunway << "center = (" << -4*(int)j-0.5 << ", 2, 1)\n" << reflectionairplane << std::endl;
                    figNum += 1;
                }
                if (airports[i]->getRunways()[j]->getAirplaneCrossing()->getStatus() == "Crossing to Gate"){
                    figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetogate << "center = (" << -4*(int)j+0.5 << ", 4, 1)\n" << reflectionairplane << std::endl;
                    figNum += 1;
                }
            }
        }
        for (unsigned int j = 0; j < airports[i]->getRunways().size(); ++j) {
            figureinfo << "[Figure" << figNum << "]\n" << cubeinfo << "center = (" << -4*(int)j-2 << ", 2, 0)\n" << reflectiontaxipoint << std::endl;
            figureinfo << "[Figure" << figNum + 1 << "]\n" << cubeinfo << "center = (" << -4*(int)j-2 << ", 4, 0)\n" << reflectiontaxipoint << std::endl;
            figNum += 2;
            if (airports[i]->getRunways()[j]->getTaxipointToRunway() != NULL){
                figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetorunway << "center = (" << -4*(int)j-2.5 << ", 2, 1)\n" << reflectionairplane << std::endl;
                figNum += 1;
            }
            if (airports[i]->getRunways()[j]->getTaxipointToGate() != NULL){
                figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetogate << "center = (" << -4*(int)j-1.5 << ", 4, 1)\n" << reflectionairplane << std::endl;
                figNum += 1;
            }
        }
        for (int j = 0; j < airports[i]->getGates(); j +=2) {
            figureinfo << "[Figure" << figNum << "]\n" << cubeinfo << "center = (" << -4*gatesoffset << ", " << j << ", 0)\n" << reflectiongate << std::endl;
            figureinfo << "[Figure" << figNum + 1 << "]\n" << buckyballinfo << "center = (" << -4*gatesoffset-0.5 << ", " << j-0.5 << ", 1)\n" << reflectiondome << std::endl;
            figureinfo << "[Figure" << figNum + 2 << "]\n" << buckyballinfo << "center = (" << -4*gatesoffset-0.5 << ", " << j+0.5 << ", 1)\n" << reflectiondome << std::endl;
            figNum += 3;
            if (airports[i]->getGatesVector()[j] != NULL){
                if (airports[i]->getGatesVector()[j]->isAtGate()){
                    figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetorunway << "center = (" << -4*gatesoffset-0.75 << ", " << j << ", 1)\n" << reflectionairplane << std::endl;
                    figureinfo << "[Figure" << figNum + 1 << "]\n" << cylinderinfo << "center = (" << -4*gatesoffset-0.5 << ", " << j-0.5 << ", 1)\n" << reflectiondome << std::endl;
                    figNum += 2;
                }
            }
            if (airports[i]->getGatesVector()[j+1] != NULL){
                if (airports[i]->getGatesVector()[j+1]->isAtGate()){
                    figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanetorunway << "center = (" << -4*gatesoffset-0.75 << ", " << j+1 << ", 1)\n" << reflectionairplane << std::endl;
                    figureinfo << "[Figure" << figNum + 1 << "]\n" << cylinderinfo << "center = (" << -4*gatesoffset-0.5 << ", " << j+0.5 << ", 1)\n" << reflectiondome << std::endl;
                    figNum += 2;
                }
            }
        }
        output << initinfo << "nrFigures = " << figNum << std::endl << std::endl;
        output << figureinfo.rdbuf();
    }
}

void Exporter::printAirleaderMessage(int time, std::string source, std::string message) {
    REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
    std::string min = "0" + to_string(time%60);
    airleaderOutput << "[" << time/60 << ":" << min.substr(min.size()-2) << "] [" << source << "]" << std::endl << "$ " << message << std::endl << std::endl;
}

void Exporter::generateImg(std::string filename) {
    REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
    std::string command = "../Engine/engine " + filename;
    system(command.c_str());
}

void Exporter::closeAirleaderOutput() {
    REQUIRE(this->properlyInitialized(), "Exporter wasn't properly initialised.");
    airleaderOutput.close();
}
