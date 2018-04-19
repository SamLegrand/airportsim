//
// Created by sam on 16.03.18.
//

#include "importer.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <sstream>

//Help functions for importer, need to be moved to utils
int stoi(std::string const& s){
    std::stringstream ss(s);
    int i;
    ss >> i;
    return i;
}

bool isInt(std::string const& s){
    std::stringstream ss(s);
    int i;
    if(!(ss >> i).fail()){
        return true;
    }
    else{
        return false;
    }
}

bool isString(std::string const& s){
    for (int unsigned i = 0; i < s.size(); ++i) {
        if(!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || (s[i] == ' '))){
            return false;
        }
    }
    return true;
}

SuccessEnum importer::importAirport(const char *inputfilename, std::ostream &errstream, AirportSim &simulation) {
    std::vector<Airport*> airports;      //Initialise airports and airplanes containers
    std::vector<Airplane*> airplanes;
    TiXmlDocument doc;      //Initalise parser document
    if (!doc.LoadFile(inputfilename)) {     //Check for failed loading of file
        errstream << doc.ErrorDesc() << std::endl;
        return ImportAborted;
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {     //Check if file contains root element
        errstream << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return PartialImport;
    }
    std::string objectName;
    for (TiXmlElement *object = doc.FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {       //Loop over elements
        objectName = object->Value();
        if (objectName == "AIRPORT") {
            Airport* airport = new Airport();       //Initialise airport
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {       //Loop over attributes
                std::string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {     //Check for empty text container
                        errstream << elemName << " does not contain any text." << std::endl;
                        return PartialImport;
                    }
                    if(!isString(text->Value())){   //Check if input is of type string
                        errstream << elemName << " does not contain a valid string." << std::endl;
                        return PartialImport;
                    }
                    if (elemName == "name") {
                        airport->setName(text->Value());
                        continue;
                    }
                    if (elemName == "iata") {
                        airport->setIata(text->Value());
                        continue;
                    }
                    if (elemName == "callsign") {
                        airport->setCallsign(text->Value());
                        continue;
                    }
                    if (!isInt(text->Value())){     //Check if input is of type int
                        errstream << elemName << " does not contain a valid number." << std::endl;
                        return PartialImport;
                    }
                    if (elemName == "gates") {
                        airport->setGates(stoi(text->Value()));
                        continue;
                    }
                    if (elemName == "passengers") {
                        airport->setPassengers(stoi(text->Value()));
                        continue;
                    }
                    errstream << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << std::endl;
                    return PartialImport;
                }
            }
            airports.push_back(airport);
            continue;
        }
        if(objectName == "RUNWAY"){
            Runway* runway = new Runway;        //Initialise runway
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                std::string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    if (elemName == "TAXIROUTE"){
                        for (TiXmlElement *elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
                            std::string elemName2 = elem2->Value();
                            for (TiXmlNode *e2 = elem2->FirstChild(); e2 != NULL; e2 = e2->NextSibling()) {
                                TiXmlText *text2 = e2->ToText();
                                if(!isString(text2->Value())){       //Check if input is of type string
                                    errstream << elemName2 << " does not contain a string." << std::endl;
                                    return PartialImport;
                                }
                                if (elemName2 == "taxipoint"){
                                    runway->addTaxipoint(text2->Value());
                                    continue;
                                }
                                if (elemName2 == "crossing"){
                                    runway->addCrossing(text2->Value());
                                    continue;
                                }
                            }
                        }
                        break;
                    }
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {     //Check for empty text container
                        errstream << elemName << " does not contain any text." << std::endl;
                        return PartialImport;
                    }
                    if(!isString(text->Value())){       //Check if input is of type string
                        errstream << elemName << " does not contain a string." << std::endl;
                        return PartialImport;
                    }
                    if (elemName == "name") {
                        runway->setName(text->Value());
                        continue;
                    }
                    if (elemName == "airport") {
                        for (unsigned int i = 0; i < airports.size(); ++i) {
                            if (airports[i]->getIata() == text->Value()){
                                airports[i]->addRunway(runway);
                                break;
                            }
                        }
                        continue;
                    }
                    if (elemName == "type"){
                        runway->setType(text->Value());
                        continue;
                    }
                    if (!isInt(text->Value())){     //Check if input is of type int
                        errstream << elemName << " does not contain a valid number." << std::endl;
                        return PartialImport;
                    }
                    if (elemName == "length"){
                        runway->setLength(stoi(text->Value()));
                        continue;
                    }
                    errstream << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << std::endl;
                    return PartialImport;
                }
            }
            continue;
        }
        if(objectName == "AIRPLANE"){
            Airplane* airplane = new Airplane();        //Initalise airplane
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                std::string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {     //Check for empty text container
                        errstream << elemName << " does not contain any text." << std::endl;
                        return PartialImport;
                    }
                    if(!isString(text->Value())){       //Check if input is of type string
                        errstream << elemName << " does not contain a string." << std::endl;
                        return PartialImport;
                    }
                    if (elemName == "number") {
                        airplane->setNumber(text->Value());
                        continue;
                    }
                    if (elemName == "callsign") {
                        airplane->setCallsign(text->Value());
                        continue;
                    }
                    if (elemName == "model") {
                        airplane->setModel(text->Value());
                        continue;
                    }
                    if (elemName == "status") {
                        airplane->setStatus(text->Value());
                        continue;
                    }
                    if(elemName == "type"){
                        airplane->setType(text->Value());
                        continue;
                    }
                    if(elemName == "engine"){
                        airplane->setEngine(text->Value());
                        continue;
                    }
                    if(elemName == "size"){
                        airplane->setSize(text->Value());
                        continue;
                    }
                    if (!isInt(text->Value())){     //Check if input is of type int
                        errstream << elemName << " does not contain a number." << std::endl;
                        return PartialImport;
                    }
                    if (elemName == "passengers") {
                        airplane->setPassengers(stoi(text->Value()));
                        continue;
                    }
                    if (elemName == "fuel") {
                        airplane->setFuel(stoi(text->Value()));
                        continue;
                    }
                    errstream << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << std::endl;
                    return PartialImport;
                }
            }
            airplanes.push_back(airplane);
            continue;
        }
        errstream << "Invalid element name " << objectName << "." << std::endl;
        return PartialImport;
    }
    std::ofstream output;
    output.open("../output.txt", std::fstream::out);        //Write simple output to stream
    for (unsigned int i=0; i<airports.size(); ++i) {
        airports[i]->printInfo(output);
    }
    for (unsigned int i=0; i<airplanes.size(); ++i) {
        airplanes[i]->printInfo(output);
    }
    output.close();
    output.open("../graphicaloutput.txt", std::fstream::out);
    importer::writeGraphicalOutput(airports, output);
    simulation.setAirplanes(airplanes);     //Set simulation variables
    simulation.setAirports(airports);
    return Success;
}

void importer::writeGraphicalOutput(const std::vector<Airport*> &airports, std::ofstream &output){
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
                output << "TP" << currentrunway->getTaxipoints()[j/2][0] << " | " << std::endl;
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
        std::cout << "Test" << std::endl;
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
    output.close();
}
