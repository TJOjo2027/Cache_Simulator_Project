//
// Created by tojo on 12/25/2025.
//

#ifndef DATAMEM_H
#define DATAMEM_H

#include <vector>
#include <cstddef>
using namespace std;

// simple storage of memory
struct DataMemory {
    size_t memSize = 0;
    vector<char> memory;
    void initDataMemory(size_t numKB);
    void displayDataMemorySpecs();
};

#endif //DATAMEM_H
