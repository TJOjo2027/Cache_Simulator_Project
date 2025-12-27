//
// Created by tojo on 12/25/2025.
//

// THESE ARE ALL THE FUNCTIONS FOR THE CACHE OBJECT

#include "cache.h"
#include <iostream>
using namespace std;

void Cache::initCache(size_t cacheSizeInKB, size_t blockSizeInBytes) {
    // set the cache member variables to defaults
    this -> cacheSize = 1024 * cacheSizeInKB;
    this -> blockSize = blockSizeInBytes;

    // find the number of cache lines
    assert(this -> cacheSize % this -> blockSize == 0 &&
        "Cache Size Must Be a Multiple of BlockSize");
    this -> numLines = this -> cacheSize / this -> blockSize;

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

void Cache::displayCacheSpecs() {
    cout << "CACHE SIZE: " << this -> cacheSize << " KB" << endl;
    cout << "BLOCK SIZE: " << this -> blockSize << " BYTES"<< endl;
    cout << "NUMBER OF CACHE LINES: " << this -> numLines << " LINES"<< endl;
}