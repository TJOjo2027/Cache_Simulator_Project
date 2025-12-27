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
        char randomChar = (rand() % (90 - 65 + 1)) + 65;
        this -> memory[i] = randomChar;
    }
}

void DataMemory::displayDataMemorySpecs() {
    cout << "DATA MEMORY SIZE: " << this -> memSize << " KB"<< endl;
}

// implement reading and writing (simple)