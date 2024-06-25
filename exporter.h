#ifndef EXPORTER_H
#define EXPORTER_H

#include "parser.h"
#include "place.h" // 添加这个头文件
#include <vector>

using namespace std;

void exportOutput(const string& filename, const vector<Position>& positions, const Design& design);

#endif