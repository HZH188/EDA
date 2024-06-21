#ifndef EXPORTER_H
#define EXPORTER_H

#include <string>
#include <map>

using namespace std;

class Exporter {
public:
    Exporter(const string& filename);
    void exportPlacement(const map<string, pair<int, int>>& placement);

private:
    string filename;
};

#endif // EXPORTER_H

