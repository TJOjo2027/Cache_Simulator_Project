//
// Created by tojo on 12/26/2025.
//

using namespace std;
#include "simulationStats.h"
#include <iostream>

void SimulationStats::setHitTimeCycles(size_t cycles) {
    this -> hitTimeCycles = cycles;
}

void SimulationStats::setWritePenaltyCycles(size_t cycles) {
    this -> writePenaltyCycles = cycles;
}

void SimulationStats::setReadPenaltyCycles(size_t cycles) {
    this -> readPenaltyCycles = cycles;
}

void SimulationStats::printCycleStats() {
    cout << "HIT TIME: " << this -> hitTimeCycles << " CYCLES" << endl;
    cout << "MEMORY WRITE PENALTY TIME: " << this -> writePenaltyCycles << " CYCLES" << endl;
    cout << "MEMORY READ PENALTY TIME: " << this -> readPenaltyCycles << " CYCLES" << endl;
}
