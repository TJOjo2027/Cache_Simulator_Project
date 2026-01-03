//
// Created by tojo on 12/25/2025.
//

#ifndef DATAMEM_H
#define DATAMEM_H

#include <vector>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "cache.h"
using namespace std;

struct Cache; // forward declaration

// simple storage of memory
struct DataMemory {
    size_t memSize = 0;
    vector<char> memory;
    void initDataMemory(size_t numKB);
    void displayDataMemorySpecs() const;
    void visualizeDataMemory(ofstream &fileStream, Cache &cache) const;
};

#endif //DATAMEM_H
