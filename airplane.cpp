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
