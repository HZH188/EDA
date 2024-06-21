#include "parser.h"
#include "place.h"
#include "exporter.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    Parser parser(inputFile);
    parser.parse();

    Die die = parser.getDieSize();
    vector<Instance> instances = parser.getInstances();
    vector<Net> nets = parser.getNets();

    Placer placer(die, instances, nets);
    map<string, pair<int, int>> placement = placer.place();

    Exporter exporter(outputFile);
    exporter.exportPlacement(placement);

    return 0;
}

