#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

Design parseInput(const string& filename) {
    Design design;
    ifstream infile(filename);
    string line;

    while (getline(infile, line)) {
        stringstream ss(line);
        string token;
        ss >> token;

        if (token == "DieSize") {
            ss >> design.rows >> design.cols;
        } else if (token == "NumInstances") {
            ss >> design.numInstances;
            design.instances.resize(design.numInstances);
            for (int i = 0; i < design.numInstances; ++i) {
                getline(infile, line);
                ss.clear();
                ss.str(line);
                ss >> token >> design.instances[i];
            }
        } else if (token == "NumNets") {
            ss >> design.numNets;
            design.nets.resize(design.numNets);
            for (int i = 0; i < design.numNets; ++i) {
                getline(infile, line);
                ss.clear();
                ss.str(line);
                ss >> token >> design.nets[i].name;
                int numPins;
                ss >> numPins;
                design.nets[i].pins.resize(numPins);
                for (int j = 0; j < numPins; ++j) {
                    getline(infile, line);
                    ss.clear();
                    ss.str(line);
                    ss >> token >> design.nets[i].pins[j];
                }
            }
        }
    }

    infile.close();
    return design;
}