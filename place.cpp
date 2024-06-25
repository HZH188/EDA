#include "place.h"
#include <cmath>
#include <algorithm>
#include <climits>
#include <unordered_set>

// 计算两个单元之间的曼哈顿距离
int manhattanDistance(const Position& a, const Position& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// 计算当前布置方案的总线长
int calculateTotalWireLength(const vector<Position>& positions, const Design& design, const unordered_map<string, int>& instanceMap) {
    int totalLength = 0;
    for (const auto& net : design.nets) {
        for (size_t i = 0; i < net.pins.size(); ++i) {
            for (size_t j = i + 1; j < net.pins.size(); ++j) {
                int idx1 = instanceMap.at(net.pins[i]);
                int idx2 = instanceMap.at(net.pins[j]);
                totalLength += manhattanDistance(positions[idx1], positions[idx2]);
            }
        }
    }
    return totalLength;
}

// 检查布局是否对称（旋转对称和反射对称）
bool isSymmetric(const vector<Position>& positions, int rows, int cols) {
    unordered_set<Position> positionSet(positions.begin(), positions.end());
    // 旋转90度对称
    for (const auto& pos : positions) {
        if (positionSet.find({cols - 1 - pos.y, pos.x}) == positionSet.end()) {
            return false;
        }
    }
    // 反射对称（水平和垂直）
    for (const auto& pos : positions) {
        if (positionSet.find({pos.x, rows - 1 - pos.y}) == positionSet.end() &&
            positionSet.find({cols - 1 - pos.x, pos.y}) == positionSet.end()) {
            return false;
        }
    }
    return true;
}

// 递归放置单元，使用剪枝和对称性处理
void placeUnits(int idx, vector<Position>& positions, vector<Position>& bestPlacement, int& minLength, const Design& design, unordered_map<string, int>& instanceMap, unordered_set<Position>& used) {
    if (idx == design.numInstances) {
        int currentLength = calculateTotalWireLength(positions, design, instanceMap);
        if (currentLength < minLength) {
            minLength = currentLength;
            bestPlacement = positions;
        }
        return;
    }

    for (int i = 0; i < design.rows; ++i) {
        for (int j = 0; j < design.cols; ++j) {
            Position pos = {i, j};
            if (used.find(pos) == used.end()) {
                positions[idx] = pos;
                used.insert(pos);
                int currentLength = calculateTotalWireLength(positions, design, instanceMap);
                if (currentLength < minLength && !isSymmetric(positions, design.rows, design.cols)) {
                    placeUnits(idx + 1, positions, bestPlacement, minLength, design, instanceMap, used);
                }
                used.erase(pos);
            }
        }
    }
}

// 找到最优布置方案
vector<Position> findOptimalPlacement(const Design& design) {
    vector<Position> bestPlacement(design.numInstances);
    int minLength = INT_MAX;
    vector<Position> positions(design.numInstances);
    unordered_map<string, int> instanceMap;
    unordered_set<Position> used;

    for (int i = 0; i < design.numInstances; ++i) {
        instanceMap[design.instances[i]] = i;
    }

    placeUnits(0, positions, bestPlacement, minLength, design, instanceMap, used);

    return bestPlacement;
}