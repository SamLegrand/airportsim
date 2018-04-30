//
// Created by sam on 16.03.18.
//

#include "importer.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "Exporter.h"
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
    std::vector<Runway*> runwaysNotAddedToPlane;
    SuccessEnum endResult = Success;
    TiXmlDocument doc;      //Initalise parser document
    if (!doc.LoadFile(inputfilename)) {     //Check for failed loading of file
        errstream << doc.ErrorDesc() << std::endl;
        return ImportAborted;
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {     //Check if file contains root element
        errstream << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        endResult = PartialImport;
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
                        endResult = PartialImport;
                    }
                    if(!isString(text->Value())){   //Check if input is of type string
                        errstream << elemName << " does not contain a valid string." << std::endl;
                        endResult = PartialImport;
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
                        endResult = PartialImport;
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
                    endResult = PartialImport;
                }
            }
            airports.push_back(airport);
            continue;
        }
        if(objectName == "RUNWAY"){
            Runway* runway = new Runway;        //Initialise runway
            bool addedRunwayToAirport = false;
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
                                    endResult = PartialImport;
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
                        endResult = PartialImport;
                    }
                    if(!isString(text->Value())){       //Check if input is of type string
                        errstream << elemName << " does not contain a string." << std::endl;
                        endResult = PartialImport;
                    }
                    if (elemName == "name") {
                        runway->setName(text->Value());
                        continue;
                    }
                    if (elemName == "airport") {
                        for (unsigned int i = 0; i < airports.size(); ++i) {
                            if (airports[i]->getIata() == text->Value()){
                                airports[i]->addRunway(runway);
                                addedRunwayToAirport = true;
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
                        endResult = PartialImport;
                    }
                    if (elemName == "length"){
                        runway->setLength(stoi(text->Value()));
                        continue;
                    }
                    errstream << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << std::endl;
                    endResult = PartialImport;
                }
            }
            if (addedRunwayToAirport == false){
                runwaysNotAddedToPlane.push_back(runway);
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
                        endResult = PartialImport;
                    }
                    if(!isString(text->Value())){       //Check if input is of type string
                        errstream << elemName << " does not contain a string." << std::endl;
                        endResult = PartialImport;
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
                        endResult = PartialImport;
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
                    endResult = PartialImport;
                }
            }
            airplanes.push_back(airplane);
            continue;
        }
        errstream << "Invalid element name " << objectName << "." << std::endl;
        endResult = PartialImport;
    }
    if (properlyInitialized(airports, runwaysNotAddedToPlane, airplanes)){
        std::cout << "Simulation has been properly initialized, simulation will start now." << std::endl;
    }
    else{
        errstream << "Simulation has not been properly initialized." << std::endl;
        endResult = PartialImport;
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
    Exporter* exporter = new Exporter();
    output.open("../GraphicalImpression.txt", std::fstream::out);
    exporter->exportGraphicalImpression(output, airports);
    output.close();
    simulation.setAirplanes(airplanes);     //Set simulation variables
    simulation.setAirports(airports);
    return endResult;
}

bool importer::properlyInitialized(const std::vector<Airport*> &airports, const std::vector<Runway*> runwaysNotAddedToPlane, const std::vector<Airplane*> &airplanes){
    if (!runwaysNotAddedToPlane.empty()){
        return false;
    }
    for (unsigned int i = 0; i < airplanes.size(); ++i) {
        if ((airplanes[i]->getType() == "private" &&
            airplanes[i]->getSize() == "small" &&
                (airplanes[i]->getEngine() == "propeller" ||
                airplanes[i]->getEngine() == "jet"))){
            continue;
        }
        if ((airplanes[i]->getType() == "private" &&
             airplanes[i]->getSize() == "medium" &&
             airplanes[i]->getEngine() == "jet")) {
            continue;
        }
        if ((airplanes[i]->getType() == "airline" &&
             airplanes[i]->getSize() == "medium" &&
             airplanes[i]->getEngine() == "propeller")) {
            continue;
        }
        if ((airplanes[i]->getType() == "airline" &&
             airplanes[i]->getSize() == "medium" &&
             airplanes[i]->getEngine() == "jet")) {
            continue;
        }
        if ((airplanes[i]->getType() == "airline" &&
             airplanes[i]->getSize() == "large" &&
             airplanes[i]->getEngine() == "jet")) {
            continue;
        }
        if ((airplanes[i]->getType() == "military" &&
             airplanes[i]->getSize() == "small" &&
             airplanes[i]->getEngine() == "jet")) {
            continue;
        }
        if ((airplanes[i]->getType() == "military" &&
             airplanes[i]->getSize() == "large" &&
             airplanes[i]->getEngine() == "propeller")) {
            continue;
        }
        if ((airplanes[i]->getType() == "emergency" &&
             airplanes[i]->getSize() == "small" &&
             airplanes[i]->getEngine() == "propeller")) {
            continue;
        }
        return false;
    }
    for (unsigned int i = 0; i < airports.size(); ++i) {
        for (unsigned int j = 0; j < airports[i]->getRunways().size(); ++j) {
            for (unsigned int k = 0; k < airports[i]->getRunways()[j]->getCrossings().size(); ++k) {
                if(airports[i]->findRunwayByRunwayName(airports[i]->getRunways()[j]->getCrossings()[k]) == NULL){
                    return false;
                }
            }
        }
    }
    return true;
}
