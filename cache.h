//
// Created by tojo on 12/25/2025.
//

#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cassert>
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
    void initCache(size_t cacheSize, size_t blockSize);
};

#endif //CACHE_H
