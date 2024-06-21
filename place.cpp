#include "place.h"
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;
//读取main中调用的数据
Placer::Placer(const Die& die, const vector<Instance>& instances, const vector<Net>& nets)
    : die(die), instances(instances), nets(nets) {}
//求取特定布局中的最短线长
double calculateTotalWireLength(const map<string, pair<int, int>>& placement, const vector<Net>& nets) {
    double totalLength = 0.0;
    for (const auto& net : nets) {
        if (net.pins.empty()) continue;

        int minX = numeric_limits<int>::max(), minY = numeric_limits<int>::max();
        int maxX = numeric_limits<int>::min(), maxY = numeric_limits<int>::min();

        for (const auto& pin : net.pins) {
            const auto& pos = placement.at(pin);
            minX = std::min(minX, pos.first);
            minY = std::min(minY, pos.second);
            maxX = std::max(maxX, pos.first);
            maxY = std::max(maxY, pos.second);
        }
        //求取最短线长的公式，用曼哈顿距离求解该问题
        totalLength += (maxX - minX) + (maxY - minY);
    }
    return totalLength;
}
//利用递归求取全部布局
void generatePermutations(vector<pair<int, int>>& positions, vector<bool>& used, vector<string>& names, int idx, double& minLength, map<string, pair<int, int>>& bestPlacement, const vector<Net>& nets, const Die& die) {
    if (idx == static_cast<int>(names.size())) {
        map<string, pair<int, int>> placement;
        for (size_t i = 0; i < names.size(); ++i) {
            placement[names[i]] = positions[i];
        }
        double length = calculateTotalWireLength(placement, nets);
        //判断后更新数据
        if (length < minLength) {
            minLength = length;
            bestPlacement = placement;
        }
        return;
    }

    for (size_t i = 0; i < positions.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            positions[idx] = {static_cast<int>(i) % die.cols, static_cast<int>(i) / die.cols};
            generatePermutations(positions, used, names, idx + 1, minLength, bestPlacement, nets, die);
            //回溯
            used[i] = false;
        }
    }
}
    //调用place函数
map<string, pair<int, int>> Placer::place() {
    //初始化
    vector<pair<int, int>> positions(die.rows * die.cols);
    vector<bool> used(die.rows * die.cols, false);
    vector<string> names;
    //填充容器
    for (const auto& instance : instances) {
        names.push_back(instance.name);
    }
    
    double minLength = numeric_limits<double>::max();
    map<string, pair<int, int>> bestPlacement;
    
    generatePermutations(positions, used, names, 0, minLength, bestPlacement, nets, die);

    return bestPlacement;//本文件最终结果
}

