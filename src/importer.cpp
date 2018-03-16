//
// Created by sam on 16.03.18.
//

#include "importer.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <sstream>

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
    vector<Airport*> airports;
    vector<Airplane*> airplanes;
    TiXmlDocument doc;
    if (!doc.LoadFile(inputfilename)) {
        errstream << doc.ErrorDesc() << endl;
        return ImportAborted;
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {
        errstream << "Failed to load file: No root element." << endl;
        doc.Clear();
        return PartialImport;
    }
    string objectName;
    for (TiXmlElement *object = doc.FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
        objectName = object->Value();
        if (objectName == "AIRPORT") {
            Airport* airport = new Airport();
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        errstream << elemName << " does not contain any text." << endl;
                        return PartialImport;
                    }
                    if(!isString(text->Value())){
                        errstream << elemName << " does not contain a string." << endl;
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
                    if (!isInt(text->Value())){
                        cerr << elemName << " does not contain a number." << endl;
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
            Runway* runway = new Runway();
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        errstream << elemName << " does not contain any text." << endl;
                        return PartialImport;
                    }
                    if(!isString(text->Value())){
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
                    errstream << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << endl;
                    return PartialImport;
                }
            }
            continue;
        }
        if(objectName == "AIRPLANE"){
            Airplane* airplane = new Airplane();
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        errstream << elemName << " does not contain any text." << endl;
                        return PartialImport;
                    }
                    if(!isString(text->Value())){
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
                    if (!isInt(text->Value())){
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
    output.open("output.txt", fstream::out);
    for (unsigned int i=0; i<airports.size(); ++i) {
        airports[i]->printInfo(output);
    }
    for (unsigned int i=0; i<airplanes.size(); ++i) {
        airplanes[i]->printInfo(output);
    }
    output.close();
    simulation.setAirplanes(airplanes);
    simulation.setAirports(airports);
    return Success;
}
