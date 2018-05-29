//
// Created by sam on 16.03.18.
//

#include "importer.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "Exporter.h"
#include "smallairplane.h"
#include "mediumairplane.h"
#include "largeairplane.h"
#include <sstream>
#include <cstdlib>
#include <algorithm>

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
    std::vector<Runway*> runwaysNotAddedToAirport;
    std::vector<std::string> crossings;
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
                        continue;
                    }
                    if(!isString(text->Value())){   //Check if input is of type string
                        errstream << elemName << " does not contain a valid string." << std::endl;
                        endResult = PartialImport;
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
                    if (!isInt(text->Value())){     //Check if input is of type int
                        errstream << elemName << " does not contain a valid number." << std::endl;
                        endResult = PartialImport;
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
                        std::vector<std::string> taxipoints;
                        for (TiXmlElement *elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
                            std::string elemName2 = elem2->Value();
                            for (TiXmlNode *e2 = elem2->FirstChild(); e2 != NULL; e2 = e2->NextSibling()) {
                                TiXmlText *text2 = e2->ToText();
                                if (text2 == NULL) {     //Check for empty text container
                                    errstream << elemName2 << " does not contain any text." << std::endl;
                                    endResult = PartialImport;
                                    continue;
                                }
                                if(!isString(text2->Value())){       //Check if input is of type string
                                    errstream << elemName2 << " does not contain a string." << std::endl;
                                    endResult = PartialImport;
                                    continue;
                                }
                                if (elemName2 == "taxipoint"){
                                    taxipoints.push_back(text2->Value());
                                    runway->setTaxipoint(text2->Value());
                                    continue;
                                }
                                if (elemName2 == "crossing"){
                                    crossings.push_back(text2->Value());
                                    continue;
                                }
                            }
                            for (unsigned int i = 0; i < airports.size(); ++i) {
                                for (unsigned int j = 0; j < airports[i]->getRunways().size(); ++j) {
                                    if (airports[i]->getRunways()[j] == runway){
                                        if (taxipoints.size() > airports[i]->getTaxipoints().size()){
                                            airports[i]->setTaxipoints(taxipoints);
                                        }
                                        break;
                                    }
                                }
                            }
                            runway->setTaxipoint(taxipoints.back());
                        }
                        break;
                    }
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {     //Check for empty text container
                        errstream << elemName << " does not contain any text." << std::endl;
                        endResult = PartialImport;
                        continue;
                    }
                    if(!isString(text->Value())){       //Check if input is of type string
                        errstream << elemName << " does not contain a string." << std::endl;
                        endResult = PartialImport;
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
                        continue;
                    }
                    if (elemName == "length"){
                        runway->setLength(stoi(text->Value()));
                        continue;
                    }
                    errstream << "Invalid attribute type '" << elemName << "' in element " << objectName << "." << std::endl;
                    endResult = PartialImport;
                }
            }
            if (!addedRunwayToAirport){
                runwaysNotAddedToAirport.push_back(runway);
            }
            continue;
        }
        if(objectName == "AIRPLANE"){
            Airplane* airplane = new Airplane();        //Initalise airplane
            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                std::string elemName = elem->Value();
                for (TiXmlNode *e = elem->FirstChild(); e != NULL; e = e->NextSibling()) {
                    if (elemName == "FLIGHTPLAN"){
                        std::vector<std::string> taxipoints;
                        for (TiXmlElement *elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
                            std::string elemName2 = elem2->Value();
                            for (TiXmlNode *e2 = elem2->FirstChild(); e2 != NULL; e2 = e2->NextSibling()) {
                                TiXmlText *text2 = e2->ToText();
                                if (text2 == NULL) {     //Check for empty text container
                                    errstream << elemName2 << " does not contain any text." << std::endl;
                                    endResult = PartialImport;
                                    continue;
                                }
                                if(!isString(text2->Value())){       //Check if input is of type string
                                    errstream << elemName2 << " does not contain a string." << std::endl;
                                    endResult = PartialImport;
                                    continue;
                                }
                                if (elemName2 == "destination"){
                                    airplane->setDestination(text2->Value());
                                    continue;
                                }
                                if (!isInt(text2->Value())){     //Check if input is of type int
                                    errstream << elemName << " does not contain a number." << std::endl;
                                    endResult = PartialImport;
                                    continue;
                                }
                                if (elemName2 == "departure"){
                                    airplane->setDeparture(stoi(text2->Value()));
                                    continue;
                                }
                                if (elemName2 == "arrival"){
                                    airplane->setArrival(stoi(text2->Value()));
                                    continue;
                                }
                                if (elemName2 == "interval"){
                                    airplane->setInterval(stoi(text2->Value()));
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
                        continue;
                    }
                    if(!isString(text->Value())){       //Check if input is of type string
                        errstream << elemName << " does not contain a string." << std::endl;
                        endResult = PartialImport;
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
                        if (strcmp(text->Value(), "Standing at Gate") == 0){
                            airports[0]->addPlaneToGate(airplane, airports[0]->getAvailableGate());
                        }
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
                        std::string size = text->Value();
                        if (size == "small"){
                            airplane = new SmallAirplane(airplane);
                        }
                        if (size == "medium"){
                            airplane = new MediumAirplane(airplane);
                        }
                        if (size == "large"){
                            airplane = new LargeAirplane(airplane);
                        }
                        continue;
                    }
                    if (!isInt(text->Value())){     //Check if input is of type int
                        errstream << elemName << " does not contain a number." << std::endl;
                        endResult = PartialImport;
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
    int unique = namesAreUnique(airports, airplanes);
    if (endResult != PartialImport && unique != 0){
        switch(unique){
            case 1:
                errstream << "Not all iata's are unique." << std::endl;
                break;
            case 2:
                errstream << "Not all airplane numbers are unique." << std::endl;
                break;
            case 3:
                errstream << "Not all runway names are unique." << std::endl;
                break;
        }
        endResult = PartialImport;
    }
    if (endResult != PartialImport && !setSquawkCodes(airplanes)){
        errstream << "One or more airplanes do not contain a possible combination of properties." << std::endl;
        endResult = PartialImport;
    }
    if (endResult != PartialImport && !enoughTaxipoints(airports)){
        errstream << "The number of taxipoints does not match the number of runways." << std::endl;
        endResult = PartialImport;
    }
    if (endResult != PartialImport && !planesCanLand(airports, airplanes)){
        errstream << "Not all planes can land on a runway." << std::endl;
        endResult = PartialImport;
    }
    if (endResult != PartialImport && !correctCrossings(airports, crossings)){
        errstream << "One or more crossings don't match a runway." << std::endl;
        endResult = PartialImport;
    }
    if (endResult != PartialImport && !runwaysNotAddedToAirport.empty()){
        errstream << "The following runways have not been added to an airport:" << std::endl;
        for (unsigned int i = 0; i < runwaysNotAddedToAirport.size(); ++i) {
            errstream << runwaysNotAddedToAirport[i]->getName() << std::endl;
        }
        endResult = PartialImport;
    }
    else if (endResult != PartialImport){
        std::cout << "Simulation has been properly initialized, simulation will start now." << std::endl;
    }
    std::ofstream output;
    output.open("../output.txt", std::fstream::out);        //Write simple output to stream
    Exporter exporter;
    exporter.exportSimpleOutput(output, airports, airplanes);
    output.close();
    simulation.setAirplanes(airplanes);     //Set simulation variables
    simulation.setAirports(airports);
    return endResult;
}

int importer::namesAreUnique(const std::vector<Airport*> &airports, const std::vector<Airplane*> &airplanes){
    // Verify unique airport iata's
    std::vector<std::string> iatas;
    for (unsigned int i = 0; i < airports.size(); ++i) {
        if (std::find(iatas.begin(), iatas.end(), airports[i]->getIata()) != iatas.end()){
            return 1;
        }
        iatas.push_back(airports[i]->getIata());
    }
    iatas.clear();

    // Verify unique airplane numbers
    std::vector<std::string> numbers;
    for (unsigned int i = 0; i < airplanes.size(); ++i) {
        if (std::find(numbers.begin(), numbers.end(), airplanes[i]->getNumber()) != numbers.end()){
            return 2;
        }
        numbers.push_back(airplanes[i]->getNumber());
    }
    numbers.clear();

    // Verify unique runway names per airport
    std::vector<std::string> runwayidentifiers;
    for (unsigned int i = 0; i < airports.size(); ++i) {
        for (unsigned int j = 0; j < airports[i]->getRunways().size(); ++j) {
            if (std::find(runwayidentifiers.begin(), runwayidentifiers.end(), airports[i]->getRunways()[j]->getName()) != runwayidentifiers.end()){
                return 3;
            }
            runwayidentifiers.push_back(airports[i]->getRunways()[j]->getName());
        }
        runwayidentifiers.clear();
    }
    runwayidentifiers.clear();
    return 0;
}

bool importer::setSquawkCodes(const std::vector<Airplane *> &airplanes) {
    std::vector<int> squawks;
    for (unsigned int i = 0; i < airplanes.size(); ++i) {
        if ((airplanes[i]->getType() == "private" &&
             dynamic_cast<SmallAirplane*>(airplanes[i]) &&
             (airplanes[i]->getEngine() == "propeller" ||
              airplanes[i]->getEngine() == "jet"))){
            do {
                srand(time(NULL));
                int random_number = std::rand() % 777 + 1;
                airplanes[i]->setSquawk(random_number);
            } while(std::find(squawks.begin(), squawks.end(), airplanes[i]->getSquawk()) != squawks.end());
            squawks.push_back(airplanes[i]->getSquawk());
            continue;
        }
        if ((airplanes[i]->getType() == "private" &&
             dynamic_cast<MediumAirplane*>(airplanes[i]) &&
             airplanes[i]->getEngine() == "jet")) {
            do {
                srand(time(NULL));
                int random_number = std::rand() % 777 + 1001;
                airplanes[i]->setSquawk(random_number);
            } while(std::find(squawks.begin(), squawks.end(), airplanes[i]->getSquawk()) != squawks.end());
            squawks.push_back(airplanes[i]->getSquawk());
            continue;
        }
        if ((airplanes[i]->getType() == "airline" &&
             dynamic_cast<MediumAirplane*>(airplanes[i]) &&
             airplanes[i]->getEngine() == "propeller")) {
            do {
                srand(time(NULL));
                int random_number = std::rand() % 777 + 2001;
                airplanes[i]->setSquawk(random_number);
            } while(std::find(squawks.begin(), squawks.end(), airplanes[i]->getSquawk()) != squawks.end());
            squawks.push_back(airplanes[i]->getSquawk());
            continue;
        }
        if ((airplanes[i]->getType() == "airline" &&
             dynamic_cast<MediumAirplane*>(airplanes[i]) &&
             airplanes[i]->getEngine() == "jet")) {
            do {
                srand(time(NULL));
                int random_number = std::rand() % 777 + 3001;
                airplanes[i]->setSquawk(random_number);
            } while(std::find(squawks.begin(), squawks.end(), airplanes[i]->getSquawk()) != squawks.end());
            squawks.push_back(airplanes[i]->getSquawk());
            continue;
        }
        if ((airplanes[i]->getType() == "airline" &&
             dynamic_cast<LargeAirplane*>(airplanes[i]) &&
             airplanes[i]->getEngine() == "jet")) {
            do {
                srand(time(NULL));
                int random_number = std::rand() % 777 + 4001;
                airplanes[i]->setSquawk(random_number);
            } while(std::find(squawks.begin(), squawks.end(), airplanes[i]->getSquawk()) != squawks.end());
            squawks.push_back(airplanes[i]->getSquawk());
            continue;
        }
        if ((airplanes[i]->getType() == "military" &&
             dynamic_cast<SmallAirplane*>(airplanes[i]) &&
             airplanes[i]->getEngine() == "jet")) {
            do {
                srand(time(NULL));
                int random_number = std::rand() % 777 + 5001;
                airplanes[i]->setSquawk(random_number);
            } while(std::find(squawks.begin(), squawks.end(), airplanes[i]->getSquawk()) != squawks.end());
            squawks.push_back(airplanes[i]->getSquawk());
            continue;
        }
        if ((airplanes[i]->getType() == "military" &&
             dynamic_cast<LargeAirplane*>(airplanes[i]) &&
             airplanes[i]->getEngine() == "propeller")) {
            do {
                srand(time(NULL));
                int random_number = std::rand() % 777 + 5001;
                airplanes[i]->setSquawk(random_number);
            } while(std::find(squawks.begin(), squawks.end(), airplanes[i]->getSquawk()) != squawks.end());
            squawks.push_back(airplanes[i]->getSquawk());
            continue;
        }
        if ((airplanes[i]->getType() == "emergency" &&
             dynamic_cast<SmallAirplane*>(airplanes[i]) &&
             airplanes[i]->getEngine() == "propeller")) {
            do {
                srand(time(NULL));
                int random_number = std::rand() % 777 + 6001;
                airplanes[i]->setSquawk(random_number);
            } while(std::find(squawks.begin(), squawks.end(), airplanes[i]->getSquawk()) != squawks.end());
            squawks.push_back(airplanes[i]->getSquawk());
            continue;
        }
        return false;
    }
    return true;
}

bool importer::enoughTaxipoints(const std::vector<Airport*> &airports){
    for (unsigned int i = 0; i < airports.size(); ++i) {
        if (airports[i]->getRunways().size() != airports[i]->getTaxipoints().size()){
            return false;
        }
    }
    return true;
}

bool importer::planesCanLand(const std::vector<Airport*> &airports, const std::vector<Airplane*> &airplanes){
    bool canLand = true;
    for (unsigned int i = 0; i < airports.size(); ++i) {
        for (unsigned int k = 0; k < airplanes.size(); ++k) {
            if (airports[i]->getRunwayByAirplane(airplanes[k])){
                continue;
            }
            canLand = false;
        }
    }
    return canLand;
}

bool importer::correctCrossings(const std::vector<Airport*> &airports, const std::vector<std::string> &crossings){
    for (unsigned int i = 0; i < airports.size(); ++i) {
        for (unsigned int j = 0; j < airports[i]->getRunways().size(); ++j) {
            for (unsigned int k = 0; k < crossings.size(); ++k) {
                if(airports[i]->findRunwayByRunwayName(crossings[k]) == NULL){
                    return false;
                }
            }
        }
    }
    return true;
}
