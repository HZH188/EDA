#ifndef PLACE_H
#define PLACE_H

#include "parser.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Position {
    int x;
    int y;
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template<>
    struct hash<Position> {
        size_t operator()(const Position& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };
}

vector<Position> findOptimalPlacement(const Design& design);

#endif