#include "parser.h"
#include "place.h"
#include "exporter.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    auto start = high_resolution_clock::now();

    Design design = parseInput(inputFile);
    vector<Position> optimalPlacement = findOptimalPlacement(design);
    exportOutput(outputFile, optimalPlacement, design);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution Time: " << duration.count() << " milliseconds" << endl;

    return 0;
}