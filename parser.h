#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

using namespace std;

struct Net {
    string name;
    vector<string> pins;
};

struct Design {
    int rows;
    int cols;
    int numInstances;
    int numNets;
    vector<string> instances;
    vector<Net> nets;
};

Design parseInput(const string& filename);

#endif