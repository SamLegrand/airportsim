#include <iostream>
#include "tinystr.h"
#include "tinyxml.h"
#include "tinyxmlparser.cpp"

using namespace std;

int main() {
    TiXmlDocument doc;
    if (!doc.LoadFile("../input.xml")) {
        cerr << doc.ErrorDesc() << endl;
        return 1;
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == nullptr) {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
        return 1;
    }
    for (TiXmlElement *object = root->FirstChildElement(); object != nullptr; object = object->NextSiblingElement()) {
        for (TiXmlElement *elem = object->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
            string elemName = elem->Value();
            if (elemName == "airport") {
                title = "";
                for (TiXmlNode *e = elem->FirstChild(); e != nullptr; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << "CD does not contain title." << endl;
                        continue;
                    }
                    title = text->Value();
                }
                if (title == "") {
                    cerr << "CD does not contain title." << endl;
                }
            } else if (elemName == "ARTIST") {
                for (TiXmlNode *e = elem->FirstChild(); e != nullptr; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << "CD does not contain artist." << endl;
                        continue;
                    }
                    artist = text->Value();
                }
            } else if (elemName == "PRICE") {
                for (TiXmlNode *e = elem->FirstChild(); e != nullptr; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << "CD does not contain price." << endl;
                        continue;
                    }
                    price = text->Value();
                }
            } else if (elemName == "YEAR") {
                for (TiXmlNode *e = elem->FirstChild(); e != nullptr; e = e->NextSibling()) {
                    TiXmlText *text = e->ToText();
                    if (text == NULL) {
                        cerr << "CD does not contain year." << endl;
                        continue;
                    }
                    year = text->Value();
                }
            }
        }
        std::cout << "Hello, World!" << std::endl;
        return 0;
    }
}