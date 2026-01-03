//
// Created by tojo on 12/25/2025.
//

// THESE ARE ALL THE FUNCTIONS FOR THE DATA MEMORY OBJECT

#include "dataMem.h"
#include <cstdlib>
#include <iostream>
#include <ostream>
using namespace std;


void DataMemory::initDataMemory(size_t numKB) {
    this -> memSize = 1024 * numKB; // convert to KB
    this -> memory.resize(this -> memSize);

    // create the data inside the data memory
    for (size_t i = 0; i < this -> memSize; i++) {
        // generate a random character from A - Z
        char randomChar = static_cast<char>((rand() % (90 - 65 + 1)) + 65);
        this -> memory[i] = randomChar;
    }
}

void DataMemory::displayDataMemorySpecs() const{
    cout << "DATA MEMORY SIZE: " << this -> memSize << " KB"<< endl;
}

void DataMemory::visualizeDataMemory(ofstream &fileStream, Cache &cache) const {
    assert(fileStream.is_open() && "Cache Visualization couldn't be opened!");

    fileStream << "Block Size: " << cache.blockSize << " bytes" << endl;

    for (size_t block = 0; block < memSize / cache.blockSize; block++) {
        fileStream << "Block " << block << endl << endl;

        // calculate the largest index in this specific block
        size_t maxIndexInBlock = (block + 1) * cache.blockSize - 1;

        // adding +1 for extra padding
        int cellWidth = static_cast<int>(log10(maxIndexInBlock)) + 1;

        // set the default
        if (cellWidth < 3) {
            cellWidth = 3;
        }

        fileStream << left << setw(8) << "Index" << '|';
        for (size_t offset = 0; offset < cache.blockSize; offset++) {
            fileStream << left << setw(cellWidth) << (block * cache.blockSize + offset) << "|";
        }
        fileStream << endl;

        fileStream << left << setw(8) << "Data" << '|';
        for (size_t index = 0; index < cache.blockSize; index++) {
            fileStream << left << setw(cellWidth) << static_cast<char>(memory[(block * cache.blockSize) + index]) << "|";
        }
        fileStream << endl << endl;
    }
}