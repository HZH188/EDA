#include "exporter.h"
#include <fstream>
#include <iostream>

void exportOutput(const string& filename, const vector<Position>& positions, const Design& design) {
    ofstream outfile(filename);
    for (size_t i = 0; i < design.instances.size(); ++i) {
        outfile << design.instances[i] << " " << positions[i].x << " " << positions[i].y << endl;
    }
    outfile.close();
}