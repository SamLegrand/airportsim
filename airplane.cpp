//
// Created by sam on 01.03.18.
//

#include "airplane.h"

void Airplane::setNumber(string _number) {
    number = _number;
}

void Airplane::setCallsign(string _callsign){
    callsign = _callsign;
}

void Airplane::setModel(string _model) {
    model = _model;
}

void Airplane::setStatus(string _status) {
    status = _status;
}

void Airplane::setPassengers(int _passengers) {
    passengers = _passengers;
}

void Airplane::setFuel(int _fuel) {
    fuel = _fuel;
}

void Airplane::printInfo() {
    cout << "Airplane: " << callsign << " (" << number << ")" << endl;
    cout << " -> model: " << model << endl;
}

void Airplane::printTestingInfo() {
    cout << number << endl;
    cout << callsign << endl;
    cout << model << endl;
    cout << status << endl;
    cout << passengers << endl;
    cout << fuel << endl;
}

void Airplane::land(Airport* airport) {
    height = 10000;
    if (status == "Approaching") {
        cout << callsign << " is approaching " << airport->getName() << " at " << height << " ft." << endl;
        while (height > 1000) {
            height = height - 1000;
            cout << callsign << " descended to " << height << " ft." << endl;
        }
        cout << callsign << " is landing at " << airport->getName() << " on runway " << airport->getAvailableRunway()->getName() << endl;
        cout << callsign << " has landed at " << airport->getName() << " on runway " << airport->getAvailableRunway()->getName() << endl;
        cout << callsign << " is taxiing to Gate " << 1 << endl;
        cout << callsign << " is standing at Gate " << 1 << endl;
    }
}
