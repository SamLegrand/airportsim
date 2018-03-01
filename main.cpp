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

int stoi(string const s){
    stringstream ss(s);
    int i;
    ss >> i;
    return i;
}

int main() {
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
    string object = root->Value();
    if (object == "AIRPORT") {
        Airport airport;
        for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
            string elemName = elem->Value();
            if (elemName == "name") {
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << "CD does not contain title." << endl;
                        continue;
                    }
                    airport.setName(text->Value());
                }
            } else if (elemName == "iata") {
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << "CD does not contain artist." << endl;
                        continue;
                    }
                    airport.setIata(text->Value());
                }
            } else if (elemName == "callsign") {
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << "CD does not contain price." << endl;
                        continue;
                    }
                    airport.setCallsign(text->Value());
                }
            } else if (elemName == "gates") {
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << "CD does not contain year." << endl;
                        continue;
                    }
                    airport.setGates(stoi(text->Value()));
                }
            } else if (elemName == "passengers") {
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << "CD does not contain year." << endl;
                        continue;
                    }
                    airport.setPassengers(stoi(text->Value()));
                }
            }
        }
        airport.printInfo();
    }
    return 0;
}