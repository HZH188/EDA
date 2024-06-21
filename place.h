#ifndef PLACE_H
#define PLACE_H

#include <vector>
#include <map>
#include <string>
#include "parser.h"

using namespace std;

class Placer {
public:
    Placer(const Die& die, const vector<Instance>& instances, const vector<Net>& nets);
    map<string, pair<int, int>> place();

private:
    Die die;
    vector<Instance> instances;
    vector<Net> nets;
};

#endif // PLACE_H

