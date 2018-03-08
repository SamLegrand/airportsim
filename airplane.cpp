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

void Airplane::setHeight(int _height) {
    height = _height;
}

void Airplane::printInfo(ofstream &output) {
    output << "Airplane: " << callsign << " (" << number << ")" << endl;
    output << " -> model: " << model << endl;
}

void Airplane::printTestingInfo() {
    cout << number << endl;
    cout << callsign << endl;
    cout << model << endl;
    cout << status << endl;
    cout << passengers << endl;
    cout << fuel << endl;
}

void Airplane::approach(string airport) {
    cout << callsign << " is approaching " << airport << " at " << height << " ft." << endl;
    status = "Descending";
}

void Airplane::descend() {
    height = height - 1000;
    cout << callsign << " descended to " << height << " ft." << endl;
    if (height == 1000) {
        status = "Landing";
    }
}

void Airplane::land(string airport, string runway) {
    cout << callsign << " is landing at " << airport << " on runway " << runway << endl;
    status = "Landed";
    height = 0;
}

void Airplane::landed(string airport, string runway) {
    cout << callsign << " has landed at " << airport << " on runway " << runway << endl;
    status = "Awaiting Taxi";
}

string Airplane::getStatus() {
    return status;
}




