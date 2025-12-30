#include <iostream>
#include <iomanip>
#include "cache.h"
#include "dataMem.h"
#include "simulationStats.h"

using namespace std;

int main() {
    cout << "Welcome to the Cache Simulator!" << endl;

    // ## SET UP SIMULATOR SETTINGS ##

    // initialize the cache
    cout << "How many KB is the cache for the simulation (no more than 5):" << endl;
    size_t numKBCache;
    cin >> numKBCache;
    assert(numKBCache > 0
        && numKBCache <= 5
        && "Number of KBCache must be less than 5");

    cout << "How big are the blocks in the cache (in bytes)?" << endl;
    size_t sizeBytesCacheBlocks;
    cin >> sizeBytesCacheBlocks;
    assert(sizeBytesCacheBlocks <= numKBCache * 1024
        && sizeBytesCacheBlocks > 0
        && "Size of block(s) must be less than the cache size");

    Cache cache;
    cache.initCache(numKBCache, sizeBytesCacheBlocks);

    cout << endl;
    cout << "CACHE CREATED!" << endl;
    cout << setw(14) << setfill('=') << "" << setfill(' ') << endl << endl;
    cache.displayCacheSpecs();

    // initialize the data memory
    DataMemory dataMemory;
    dataMemory.initDataMemory(numKBCache * 4);

    cout << endl;
    cout << "DATA MEMORY CREATED!" << endl;
    cout << setw(20) << setfill('=') << "" << setfill(' ') << endl << endl;
    dataMemory.displayDataMemorySpecs();

    cout << endl;

    SimulationStats simulationStats;
    cout << "CURRENT TIME CONFIGURATIONS" << endl;
    cout << setw(27) << setfill('=') << "" << setfill(' ') << endl << endl;
    simulationStats.printCycleStats();

    cout << endl;
    char timingConfigQuestionChar;
    bool timingConfigQuestion = false;
    while (!timingConfigQuestion) {
        cout << "Are these configurations ok? (Enter Y/N)" << endl;
        cin >> timingConfigQuestionChar;

        if (timingConfigQuestionChar == 'Y'
            || timingConfigQuestionChar == 'y') {
            timingConfigQuestion = true;
        }
        else if (timingConfigQuestionChar == 'N'
            || timingConfigQuestionChar == 'n') {
            // have some setters to change setting
            size_t hitTimeCycles;
            size_t writePenaltyCycles;
            size_t readPenaltyCycles;

            cout << "Change Hit Time (cycles)" << endl;
            cin >> hitTimeCycles;
            simulationStats.setHitTimeCycles(hitTimeCycles);
            cout << "Change Write Penalty Time (cycles)" << endl;
            cin >> writePenaltyCycles;
            simulationStats.setWritePenaltyCycles(writePenaltyCycles);
            cout << "Change Read Penalty Time (cycles)" << endl;
            cin >> readPenaltyCycles;
            simulationStats.setReadPenaltyCycles(readPenaltyCycles);

            cout << "NEW SIMULATION STATS" << endl;
            cout << setw(20) << setfill('=') << "" << setfill(' ') << endl << endl;
            simulationStats.printCycleStats();

            timingConfigQuestion = true;
        }
        else {
            // loops if format is wrong
            cout << "Use the correct format (Y/N)" << endl;
        }
    }

    // configuration/setup done

    cout << endl;
    cout << "FOR THE SAKE OF SIMULATION, THE CACHE WILL BE INITIAL EMPTY" << endl << endl;

    // create visualization files (text file) for the user to see the current state of the cache and data memory
    ofstream cacheStream;
    cacheStream.open("cache.txt");

    ofstream dataMemoryStream;
    dataMemoryStream.open("dataMemory.txt");

    //cache.visualizeCache(cacheStream);
    cout << "CREATED CACHE AND DATA MEMORY VISUALIZATION FILES" << endl;

    // implement cache and data memory interactions



    cacheStream.close();
    dataMemoryStream.close();

    return 0;
}
