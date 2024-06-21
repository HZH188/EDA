#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <map>

using namespace std;

struct Net {
    string name;
    vector<string> pins;
};

struct Instance {
    string name;
};

struct Die {
    int rows;
    int cols;
};

class Parser {
public:
    Parser(const string& filename);
    void parse();
    Die getDieSize() const;
    vector<Instance> getInstances() const;
    vector<Net> getNets() const;

private:
    string filename;
    Die dieSize;
    vector<Instance> instances;
    vector<Net> nets;
};

#endif // PARSER_H

