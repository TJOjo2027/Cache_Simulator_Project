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

void SimulationStats::updateSimulationStats() {

    // guard in case 0 total accesses
    if (totalAccesses == 0) {
        return;
    }

    // set hit rate
    hitRate = static_cast<double>(hits) / static_cast<double>(totalAccesses);

    // set miss rate
    missRate = static_cast<double>(misses) / static_cast<double>(totalAccesses);

    // set AMAT
    amat = static_cast<double>(hitTimeCycles) + (missRate * static_cast<double>(readPenaltyCycles));

    // set simulation time
    simulationTime = static_cast<double>(simulationCycles) * (1.0 / static_cast<double>(hitTimeCycles));
}

void SimulationStats::printStats(ofstream &printStream) {
    updateSimulationStats();
    printStream << "Total accesses: " << totalAccesses << endl;
    printStream << "Hits per access: " << hitRate << endl;
    printStream << "Misses per access: " << missRate << endl;
    printStream << "AMAT: " << amat << endl;
    printStream << "Simulation Cycles: " << simulationCycles << endl;
    printStream << "Simulation Time: " << simulationTime << endl;
}
