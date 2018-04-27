//
// Created by vyolex on 4/27/18.
//

#include "AirLeader.h"

AirLeader::AirLeader() {
    output.open("../AirControlOutput.txt", std::fstream::out);
}

void AirLeader::printMessage(const int time, std::string source, std::string message) {
    output << "[" << time << "][" << source << "]" << std::endl << "$ " << message << std::endl;
}
