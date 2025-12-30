//
// Created by tojo on 12/25/2025.
//

#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cassert>
#include <cstddef>
#include <fstream>
#include "dataMem.h"
using namespace std;

struct CacheLine {
    bool dirtyBit = false; // 1 is dirty, 0 is clean
    bool validBit = false; // 1 is valid, 0 is not
    vector <unsigned char> dataLine;
    unsigned int tag;
    unsigned int cacheIndex;

};

struct Cache {
    size_t cacheSize;
    size_t blockSize;
    size_t numLines;
    vector <CacheLine> cacheLines;
    void initCache(size_t cacheSizeInKB, size_t blockSizeInBytes);
    void displayCacheSpecs();
    void visualizeCache(ofstream& fileStream);
    void readFromMemory(DataMemory &dataMemory, size_t memoryAddress);
    void writeToMemory(DataMemory &dataMemory, size_t memoryAddress);
    size_t getBlockAddress(size_t memoryAddress);
    size_t getCacheIndex(size_t blockAddress);
    size_t getTag(size_t blockAddress);

    void getOffset();
};

#endif //CACHE_H
