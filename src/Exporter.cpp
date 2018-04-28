//
// Created by sam on 28.04.18.
//

#include <sstream>
#include "Exporter.h"

Exporter::Exporter() {
    initCheck = this;
    docStarted = false;
}

bool Exporter::properlyInitizalized() {
    return initCheck == this;
}

bool Exporter::documentStarted() {
    return docStarted;
}

void Exporter::documentStart(std::ofstream &file) {
    docStarted = true;
}

void Exporter::documentEnd(std::ofstream &file) {
    docStarted = false;
}

void Exporter::exportGraphicalImpression(std::ofstream &output, const std::vector<Airport*> &airports){
    int currentsize = 0;
    Runway* currentrunway;
    for (unsigned int i = 0; i < airports.size(); ++i) {
        for (unsigned int j = 0; j < airports[i]->getRunways().size(); ++j) {
            if ((int)airports[i]->getRunways()[j]->getTaxipoints().size() > currentsize){
                currentsize = airports[i]->getRunways()[j]->getTaxipoints().size();
                currentrunway = airports[i]->getRunways()[j];
            }
        }
        output << currentrunway->getName() << " | ";
        if (currentrunway->getAirplane() != NULL){
            output << "====V=====" << std::endl;
        }
        else{
            output << "==========" << std::endl;
        }
        int j = currentrunway->getTaxipoints().size() + currentrunway->getCrossings().size() - 1;
        while (j >= 0) {
            if (j%2 == 0){
                output << "TP" << currentrunway->getTaxipoints()[j/2]->getName()[0] << " | " << std::endl;
            }
            else{
                output << currentrunway->getCrossings()[j/2] << " | ";
                if (airports[i]->findRunway(currentrunway->getCrossings()[j/2])->getAirplane() != NULL){
                    output << "====V=====" << std::endl;
                }
                else{
                    output << "==========" << std::endl;
                }
            }
            --j;
        }
        output << "Gates [";
        for (int j = 0; j < airports[i]->getGates(); ++j) {
            if(airports[i]->getGatesVector()[j] != NULL){
                output << "V";
            }
            else{
                output << " ";
            }
        }
        output << "]" << std::endl << std::endl;
    }
}

void EngineIniExporter::exportIni(std::ofstream &output, const std::vector<Airport *> &airports){
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
            "scale = 0.25";
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
            "reflectionCoefficient = 20";
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

    //Write to ini
    for (unsigned int i = 0; i < airports.size(); ++i) {
        std::stringstream figureinfo;
        figureinfo << light << std::endl;
        int gatesoffset = airports[i]->getRunways().size();
        int figNum = 0;
        for (unsigned int j = 0; j < airports[i]->getRunways().size(); ++j) {
            figureinfo << "[Figure" << figNum << "]\n" << cubeinfo << "center = (" << -4*j << ", 0, 0)\n" << reflectionrunway << std::endl;
            figureinfo << "[Figure" << figNum + 1 << "]\n" << cubeinfo << "center = (" << -4*j << ", 2, 0)\n" << reflectionrunway << std::endl;
            figureinfo << "[Figure" << figNum + 2 << "]\n" << cubeinfo << "center = (" << -4*j << ", 4, 0)\n" << reflectionrunway << std::endl;
            figNum += 3;
            if (airports[i]->getRunways()[j]->getAirplane() != NULL){
                figureinfo << "[Figure" << figNum << "]\n" << coneinfo << airplanestanding << "center = (" << -4*j << ", -0.5, 1)\n" << reflectionairplane << std::endl;
                figNum += 1;
            }
        }
        for (unsigned int j = 0; j < airports[i]->getFarthestRunway()->getTaxipoints().size(); ++j) {
            figureinfo << "[Figure" << figNum << "]\n" << cubeinfo << "center = (" << -4*j-2 << ", 2, 0)\n" << reflectiontaxipoint << std::endl;
            figureinfo << "[Figure" << figNum + 1 << "]\n" << cubeinfo << "center = (" << -4*j-2 << ", 4, 0)\n" << reflectiontaxipoint << std::endl;
            figNum += 2;
        }
        for (int j = 0; j < airports[i]->getGates(); j +=2) {
            figureinfo << "[Figure" << figNum << "]\n" << cubeinfo << "center = (" << -4*gatesoffset << ", " << j << ", 0)\n" << reflectiongate << std::endl;
            figNum += 1;
        }
        output << initinfo << "nrFigures = " << figNum << std::endl << std::endl;
        output << figureinfo.rdbuf();
    }
}

void AirleaderExporter::printMessage(std::ofstream &output, int time, std::string source, std::string message) {
    output << "[" << time << "][" << source << "]" << std::endl << "$ " << message << std::endl;
}
