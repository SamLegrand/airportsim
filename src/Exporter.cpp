//
// Created by sam on 28.04.18.
//

#include "Exporter.h"

Exporter::Exporter() {
    initCheck = this;
    docStarted = false;
}

bool Exporter::properlyInitizalized() {
    return initCheck == this;
}

bool Exporter::documentStarted() {
    return docStarted;
}


