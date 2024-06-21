#include "exporter.h"
#include <fstream>
#include <iostream>

Exporter::Exporter(const string& filename) : filename(filename) {}

void Exporter::exportPlacement(const map<string, pair<int, int>>& placement) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    for (const auto& entry : placement) {
        file << entry.first << " " << entry.second.first << " " << entry.second.second << endl;
    }

    file.close();
}

