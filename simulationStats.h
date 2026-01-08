//
// Created by tojo on 12/26/2025.
//

#ifndef SIMULATIONSTATS_H
#define SIMULATIONSTATS_H
#include <fstream>

using namespace std;
#include <cstddef>

struct SimulationStats {

    // numeric stats
    size_t totalAccesses = 0;
    size_t hits = 0;
    size_t misses = 0;
    size_t writeBacks = 0;

    // rates
    double hitRate = 0.0;
    double missRate = 0.0;

    // timings
    size_t clockSpeed = 1; // in nano-seconds
    size_t hitTimeCycles = 1;
    size_t writePenaltyCycles = 50;
    size_t readPenaltyCycles = 50;

    // derived stats
    double amat = 0.0;
    unsigned long int simulationCycles = 0;
    double simulationTime = 0.0;

    // setters
    void setHitTimeCycles(size_t cycles);
    void setWritePenaltyCycles(size_t cycles);
    void setReadPenaltyCycles(size_t cycles);
    void setClockSpeed(size_t speedInNS);

    // displaying customizable timing
    void printCycleStats() const;

    // runtime simulation calculations
    void updateSimulationStats();
    void printStats(ofstream &printStream);
};

#endif //SIMULATIONSTATS_H
