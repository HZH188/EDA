#include "parser.h"
#include "place.h"
#include "exporter.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

//读取命令行中的三个参数

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

//第一个为输入文件，第二个为输出文件
    
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
