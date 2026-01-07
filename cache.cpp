//
// Created by tojo on 12/25/2025.
//

// THESE ARE ALL THE FUNCTIONS FOR THE CACHE OBJECT

#include "cache.h"
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cmath>

#include "dataMem.h"
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

void Cache::displayCacheSpecs() const {
    cout << "CACHE SIZE: " << this -> cacheSize << " KB" << endl;
    cout << "BLOCK SIZE: " << this -> blockSize << " BYTES"<< endl;
    cout << "NUMBER OF CACHE LINES: " << this -> numLines << " LINES"<< endl;
}

void Cache::visualizeCache(ofstream& fileStream) {
    assert(fileStream.is_open() && "Cache Visualization couldn't be opened!");

    fileStream << endl;
    fileStream << "Block Size: " << blockSize << " bytes" << endl;
    fileStream << "Number of Cache Lines: " << numLines << endl << endl;

    for (size_t i = 0; i < numLines; i++) {
        fileStream << "Index " << cacheLines[i].cacheIndex << endl << endl;

        // file formatting stuff

        // run if there is data
        if (cacheLines[i].validBit) {
            fileStream << "Tag (in Base 10): " << cacheLines[i].tag << " | ";
            fileStream << "Valid: " << cacheLines[i].validBit << " | ";
            fileStream << "Dirty: " << cacheLines[i].dirtyBit << endl;
        }
        else {
            fileStream << "Tag (in Base 10): " << "N/A" << " | ";
            fileStream << "Valid: " << cacheLines[i].validBit << " | ";
            fileStream << "Dirty: " << cacheLines[i].dirtyBit << endl;
        }

        // find the space need for the offset number to be held
        fileStream << left << setw(8) << "Offsets" << '|';
        int cellWidth = static_cast<int>(floor(log10(blockSize - 1))) + 2;
        for (size_t offset = 0; offset < blockSize; offset++) {
            fileStream  << left <<  setw(cellWidth) << offset << "|";
        }
        fileStream << endl;

        // display data
        fileStream << left << setw(8) << "Data" << '|';
        if (cacheLines[i].validBit) {
            for (size_t offset = 0; offset < blockSize; offset++) {
                fileStream  << left <<  setw(cellWidth) << static_cast<char>(cacheLines[i].dataLine[offset]) << "|";
            }
        }
        else {
            for (size_t offset = 0; offset < blockSize; offset++) {
                fileStream  << left <<  setw(cellWidth) << "-" << "|";
            }
        }
        fileStream << endl << endl;
    }
}

// Memory to Cache
void Cache::readFromMemory(DataMemory &dataMemory, size_t memoryAddress, SimulationStats &stats) {
    size_t blockAddress = getBlockAddress(memoryAddress);
    size_t cacheIndex = getCacheIndex(blockAddress);
    size_t tag = getTag(blockAddress);

    // Load block from memory into cache line
    size_t memoryOffset = blockAddress * blockSize;
    for (size_t offset = 0; offset < blockSize; ++offset, ++memoryOffset) {
        cacheLines[cacheIndex].dataLine[offset] = dataMemory.memory[memoryOffset];
    }

    // Update cache line metadata
    cacheLines[cacheIndex].validBit = true;
    cacheLines[cacheIndex].dirtyBit = false;
    cacheLines[cacheIndex].tag = tag;
}

// Cache to Memory
void Cache::writeToMemory(DataMemory &dataMemory, size_t memoryAddress, SimulationStats &stats) const {
    size_t cacheIndex = getCacheIndex(getBlockAddress(memoryAddress));
    size_t currentTag = cacheLines[cacheIndex].tag;
    size_t originalBlockAddress = (currentTag * numLines) + cacheIndex;
    size_t memoryOffset = originalBlockAddress * blockSize;
    for (size_t offset = 0; offset < blockSize; ++offset, ++memoryOffset) {
        dataMemory.memory[memoryOffset] = static_cast<char>(cacheLines[cacheIndex].dataLine[offset]);
    }
}

// This is the "Brain" of your cache
bool Cache::access(DataMemory &dataMemory, size_t memoryAddress, SimulationStats &stats, bool writeCommand) {
    size_t blockAddress = getBlockAddress(memoryAddress);
    size_t cacheIndex = getCacheIndex(blockAddress);
    size_t tag = getTag(blockAddress);

    // handles the number of access, increments it
    stats.totalAccesses++;

    // checking for a hit
    if (cacheLines[cacheIndex].validBit && cacheLines[cacheIndex].tag == tag) {
        // case of hit
        stats.hits++;
        stats.simulationCycles += stats.hitTimeCycles;

        if (writeCommand) {
            // line is dirty now
            cacheLines[cacheIndex].dirtyBit = true;
            // replacing the data at the area with asterix to show the change (dummy value)
            cacheLines[cacheIndex].dataLine[getOffset(memoryAddress)] = static_cast<char>(42);
        }
        return true;
    }

    // 2. MISS CASE
    stats.misses++;

    // check for dirty eviction penalty
    if (cacheLines[cacheIndex].validBit && cacheLines[cacheIndex].dirtyBit) {
        stats.writeBacks++;
        stats.simulationCycles += stats.writePenaltyCycles;
        // Call your writeToMemory here to save the old data
        writeToMemory(dataMemory, memoryAddress, stats);
    }

    // Fetch the new data from memory
    stats.simulationCycles += stats.readPenaltyCycles;
    readFromMemory(dataMemory, memoryAddress, stats);

    // If it was a WRITE miss, we mark it dirty after fetching it
    if (writeCommand) {
        cacheLines[cacheIndex].dirtyBit = true;
    }
    // false for a miss
    return false;
}

size_t Cache::getBlockAddress(size_t memAddress) const {
    return memAddress / blockSize;
}

size_t Cache::getOffset(size_t memoryAddress) const {
    return memoryAddress % blockSize;
}

size_t Cache::getCacheIndex(size_t blockAddress) const {
    return blockAddress % numLines;
}

size_t Cache::getTag(size_t blockAddress) const {
    return blockAddress / numLines;
}