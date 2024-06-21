#include "parser.h"
#include "place.h"
#include "exporter.h"
#include <iostream>
//检查命令行参数，./EDA_Assess input.txt output.txt规范格式
int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
//读取命令行参数
    string inputFile = argv[1];
    string outputFile = argv[2];
//读取文件
    Parser parser(inputFile);
    parser.parse();
//初始化
    Die die = parser.getDieSize();
    vector<Instance> instances = parser.getInstances();
    vector<Net> nets = parser.getNets();
//算法
    Placer placer(die, instances, nets);
    map<string, pair<int, int>> placement = placer.place();
//输出
    Exporter exporter(outputFile);
    exporter.exportPlacement(placement);

    return 0;
}

