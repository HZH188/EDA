#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

Parser::Parser(const string& filename) : filename(filename) {}

void Parser::parse() {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string word;
        ss >> word;
        if (word == "DieSize") {
            ss >> dieSize.rows >> dieSize.cols;
        } else if (word == "NumInstances") {
            int numInstances;
            ss >> numInstances;
            for (int i = 0; i < numInstances; ++i) {
                getline(file, line);
                stringstream ssInstance(line);
                string instKeyword, instName;
                ssInstance >> instKeyword >> instName;
                instances.push_back({instName});
            }
        } else if (word == "NumNets") {
            int numNets;
            ss >> numNets;
            for (int i = 0; i < numNets; ++i) {
                getline(file, line);
                stringstream ssNet(line);
                string netKeyword, netName;
                int numPins;
                ssNet >> netKeyword >> netName >> numPins;
                Net net = {netName, {}};
                for (int j = 0; j < numPins; ++j) {
                    getline(file, line);
                    stringstream ssPin(line);
                    string pinKeyword, pinName;
                    ssPin >> pinKeyword >> pinName;
                    net.pins.push_back(pinName);
                }
                nets.push_back(net);
            }
        }
    }
    file.close();
}

Die Parser::getDieSize() const {
    return dieSize;
}

vector<Instance> Parser::getInstances() const {
    return instances;
}

vector<Net> Parser::getNets() const {
    return nets;
}

