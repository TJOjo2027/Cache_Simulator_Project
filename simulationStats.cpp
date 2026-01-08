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

void SimulationStats::setClockSpeed(size_t speedInNS) {
    this -> clockSpeed = speedInNS;
}

void SimulationStats::printCycleStats() const {
    cout << "CLOCK SPEED: " << this -> clockSpeed << " NS PER CYCLE" << endl;
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
    simulationTime = static_cast<double>(simulationCycles) * static_cast<double>(clockSpeed);
}

void SimulationStats::printStats(ofstream &printStream) {
    updateSimulationStats();
    printStream << "Total accesses: " << totalAccesses  << " accesses" << endl;

    // multiplying by 100 to get the number not a decimal < 0
    printStream << "Hits per access: " << hitRate * 100 << "%" << endl;
    printStream << "Misses per access: " << missRate * 100 << "%" << endl;

    printStream << "AMAT: " << amat << " cycles" << endl;
    printStream << "Simulation Cycles: " << simulationCycles << " cycles" << endl;
    printStream << "Simulation Time: " << simulationTime << " ns" << endl;
}
