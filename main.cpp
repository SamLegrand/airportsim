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
                    if (elemName == "gates") {
                        airport->setGates(stoi(text->Value()));
                        continue;
                    }
                    if (elemName == "passengers") {
                        airport->setPassengers(stoi(text->Value()));
                        continue;
                    }
                }
            }
            airports.push_back(airport);
            //airport->printInfo();
        }
        else if(objectName == "RUNWAY"){
            Runway* runway = new Runway();
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << elemName << " does not contain any text." << endl;
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
                }
            }
            //runway->printInfo();
        }
        else if(objectName == "AIRPLANE"){
            Airplane* airplane = new Airplane();
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << elemName << " does not contain any text." << endl;
                        continue;
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
                    if (elemName == "passengers") {
                        airplane->setPassengers(stoi(text->Value()));
                        continue;
                    }
                    if (elemName == "fuel") {
                        airplane->setFuel(stoi(text->Value()));
                        continue;
                    }
                }
            }
            airplanes.push_back(airplane);
            //airplane.printTestingInfo();
        }
    }
    for (unsigned int i=0; i<airports.size(); ++i) {
        airports[i]->printInfo();
    }
    for (unsigned int i=0; i<airplanes.size(); ++i) {
        airplanes[i]->printInfo();
        airplanes[i]->land(airports[0]);
    }

    return 0;
}