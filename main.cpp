#include <iostream>
#include "tinystr.h"
#include "tinyxml.h"
#include "tinyxmlparser.cpp"
#include "airport.h"
#include "airplane.h"
#include "runway.h"
#include <vector>
#include <sstream>

using namespace std;

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

int main() {
    vector<Airport*> airports;
    vector<Airplane*> airplanes;
    TiXmlDocument doc;
    if (!doc.LoadFile("../input.xml")) {
        cerr << doc.ErrorDesc() << endl;
        return 1;
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
        return 1;
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
                        cerr << elemName << " does not contain any text." << endl;
                        continue;
                    }
                    if(!isString(text->Value())){
                        cerr << elemName << " does not contain a string." << endl;
                        continue;
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
                        continue;
                    }
                    if (elemName == "gates") {
                        for (int i=0; i<stoi(text->Value()); i++) {
                            airport->addGate(new Gate);
                        }
                        continue;
                    }
                    if (elemName == "passengers") {
                        airport->setPassengers(stoi(text->Value()));
                        continue;
                    }
                    cerr << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << endl;
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
                        cerr << elemName << " does not contain any text." << endl;
                        continue;
                    }
                    if(!isString(text->Value())){
                        cerr << elemName << " does not contain a string." << endl;
                        continue;
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
                    cerr << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << endl;
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
                        cerr << elemName << " does not contain any text." << endl;
                        continue;
                    }
                    if(!isString(text->Value())){
                        cerr << elemName << " does not contain a string." << endl;
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
                        cerr << elemName << " does not contain a number." << endl;
                        continue;
                    }
                    if (elemName == "passengers") {
                        airplane->setPassengers(stoi(text->Value()));
                        continue;
                    }
                    if (elemName == "fuel") {
                        airplane->setFuel(stoi(text->Value()));
                        continue;
                    }
                    cerr << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << endl;
                }
            }
            airplane->setHeight(10000);
            airplanes.push_back(airplane);
            continue;
        }
        cerr << "Invalid element name " << objectName << "." << endl;
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
    return 0;
}

void Planelanding(Airplane* airplane, Airport* destination) {
    if (airplane->getStatus() == "Approaching") {
        airplane->approach(destination->getName());
    }
    if (airplane->getStatus() == "Descending") {
        airplane->descend();
    }
    if (airplane->getStatus() == "Landing") {
        airplane->land(destination->getName(), destination->getAvailableRunway()->getName());
    }
    if (airplane->getStatus() == "Landed") {
        airplane->landed(destination->getName(), destination->getAvailableRunway()->getName());
    }
    if (airplane->getStatus() == "Awaiting Taxi") {

    }

//        cout << callsign << " is taxiing to Gate " << 1 << endl;
//
//        cout << callsign << " is standing at Gate " << 1 << endl;
//        status = "Standing at Gate";
}