//
// Created by tojo on 12/25/2025.
//

// THESE ARE ALL THE FUNCTIONS FOR THE CACHE OBJECT

#include "cache.h"
using namespace std;

void Cache::initCache(size_t cacheSize, size_t blockSize) {
    // set the cache member variables to defaults
    this -> cacheSize = cacheSize;
    this -> blockSize = blockSize;

    // find the number of cache lines
    assert(cacheSize % blockSize == 0 && "Cache Size Must Be a Multiple of BlockSize");
    this -> numLines = cacheSize / blockSize;

    // resize cacheLines vector
    this -> cacheLines.resize(this -> numLines);

    // for cache lines, resize data to block size and set the data members to defaults
    for (size_t i = 0; i < this -> cacheLines.size(); i++) {
        this -> cacheLines[i].dataLine.resize(this -> blockSize);
        this -> cacheLines[i].validBit = false;
        this -> cacheLines[i].dirtyBit = false;
        this -> cacheLines[i].tag = 0;
        this -> cacheLines[i].cacheIndex = i;
    }
}