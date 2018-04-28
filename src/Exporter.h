//
// Created by sam on 28.04.18.
//

#ifndef AIRPORTSIM_EXPORTER_H
#define AIRPORTSIM_EXPORTER_H


class Exporter {
private:
    Exporter* initCheck;
    bool docStarted;
public:
    Exporter();
    bool properlyInitizalized();
    bool documentStarted();
    virtual void documentStart();
    virtual void documentEnd();
};

class GraphicalTextExporter: public Exporter {
    virtual void documentStart();
};


#endif //AIRPORTSIM_EXPORTER_H
