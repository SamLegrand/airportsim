//
// Created by sam on 16.03.18.
//

#include "importer.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <sstream>

//Help functions for importer, need to be moved to utils
int stoi(string const& s){
    stringstream ss(s);
    int i;
    ss >> i;
    return i;
}

bool isInt(string const& s){
    stringstream ss(s);
    int i;
    if(!(ss >> i).fail()){
        return true;
    }
    else{
        return false;
    }
}

bool isString(string const& s){
    for (int unsigned i = 0; i < s.size(); ++i) {
        if(!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || (s[i] == ' '))){
            return false;
        }
    }
    return true;
}

SuccessEnum importer::importAirport(const char *inputfilename, std::ostream &errstream, AirportSim &simulation) {
    vector<Airport*> airports;      //Initialise airports and airplanes containers
    vector<Airplane*> airplanes;
    TiXmlDocument doc;      //Initalise parser document
    if (!doc.LoadFile(inputfilename)) {     //Check for failed loading of file
        errstream << doc.ErrorDesc() << endl;
        return ImportAborted;
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {     //Check if file contains root element
        errstream << "Failed to load file: No root element." << endl;
        doc.Clear();
        return PartialImport;
    }
    string objectName;
    for (TiXmlElement *object = doc.FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {       //Loop over elements
        objectName = object->Value();
        if (objectName == "AIRPORT") {
            Airport* airport = new Airport();       //Initialise airport
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {       //Loop over attributes
                string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {     //Check for empty text container
                        errstream << elemName << " does not contain any text." << endl;
                        return PartialImport;
                    }
                    if(!isString(text->Value())){   //Check if input is of type string
                        errstream << elemName << " does not contain a valid string." << endl;
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
                        errstream << elemName << " does not contain a valid number." << endl;
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
                    errstream << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << endl;
                    return PartialImport;
                }
            }
            airports.push_back(airport);
            continue;
        }
        if(objectName == "RUNWAY"){
            Runway* runway = new Runway;        //Initialise runway
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {     //Check for empty text container
                        errstream << elemName << " does not contain any text." << endl;
                        return PartialImport;
                    }
                    if (elemName == "TAXIROUTE"){
                        for (TiXmlElement *elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
                            string elemName2 = elem2->Value();
                            for (TiXmlNode *e2 = elem2->FirstChild(); e2 != NULL; e2 = e2->NextSibling()) {
                                TiXmlText *text2 = e2->ToText();
                                if(!isString(text2->Value())){       //Check if input is of type string
                                    errstream << elemName2 << " does not contain a string." << endl;
                                    return PartialImport;
                                }
                                if (elemName2 == "taxipoint"){
                                    runway->addTaxipoint(text2->Value());
                                }
                                if (elemName2 == "crossing"){
                                    runway->addCrossing(text2->Value());
                                }
                            }
                        }
                    }
                    if(!isString(text->Value())){       //Check if input is of type string
                        errstream << elemName << " does not contain a string." << endl;
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
                    }
                    if (!isInt(text->Value())){     //Check if input is of type int
                        errstream << elemName << " does not contain a valid number." << endl;
                        return PartialImport;
                    }
                    if (elemName == "length"){
                        runway->setLength(stoi(text->Value()));
                    }
                    errstream << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << endl;
                    return PartialImport;
                }
            }
            continue;
        }
        if(objectName == "AIRPLANE"){
            Airplane* airplane = new Airplane();        //Initalise airplane
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {     //Check for empty text container
                        errstream << elemName << " does not contain any text." << endl;
                        return PartialImport;
                    }
                    if(!isString(text->Value())){       //Check if input is of type string
                        errstream << elemName << " does not contain a string." << endl;
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
                    }
                    if(elemName == "engine"){
                        airplane->setEngine(text->Value());
                    }
                    if(elemName == "size"){
                        airplane->setSize(text->Value());
                    }
                    if (!isInt(text->Value())){     //Check if input is of type int
                        errstream << elemName << " does not contain a number." << endl;
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
                    errstream << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << endl;
                    return PartialImport;
                }
            }
            airplanes.push_back(airplane);
            continue;
        }
        errstream << "Invalid element name " << objectName << "." << endl;
        return PartialImport;
    }
    ofstream output;
    output.open("../output.txt", fstream::out);        //Write simple output to stream
    for (unsigned int i=0; i<airports.size(); ++i) {
        airports[i]->printInfo(output);
    }
    for (unsigned int i=0; i<airplanes.size(); ++i) {
        airplanes[i]->printInfo(output);
    }
    output.close();

    output.open("../graphicaloutput.txt", fstream::out);
    int currentsize = 0;
    Runway* currentrunway;
    for (int i = 0; i < airports.size(); ++i) {
        for (int j = 0; j < airports[i]->getRunways().size(); ++j) {
            if (airports[i]->getRunways()[j]->getTaxipoints().size() > currentsize){
                currentsize = airports[i]->getRunways()[j]->getTaxipoints().size();
                currentrunway = airports[i]->getRunways()[j];
            }
        }
        output << currentrunway->getName() << " | ";
        if (currentrunway->getAirplane() != NULL){
            output << "====V=====" << endl;
        }
        else{
            output << "==========" << endl;
        }
        for (int j = 0; j < currentrunway->getTaxipoints().size();) {
            if (j%2 == 0){
                output << currentrunway->getTaxipoints()[j] << " | " << endl;
                ++j;
            }
            else{
                output << currentrunway->getCrossings()[j-1] << " | ";
                if (airports[i]->findRunway(currentrunway->getCrossings()[j-1])->getAirplane() != NULL){
                    output << "====V=====" << endl;
                }
                else{
                    output << "==========" << endl;
                }
            }
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
        output << "]" << endl << endl;
    }
    output.close();
    simulation.setAirplanes(airplanes);     //Set simulation variables
    simulation.setAirports(airports);
    return Success;
}
