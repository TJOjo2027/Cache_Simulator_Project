#include <iostream>
#include <iomanip>
#include <filesystem>
#include <stdexcept>
#include <thread>
#include <chrono>
#include "cache.h"
#include "dataMem.h"
#include "simulationStats.h"

namespace fs = std::filesystem;
using namespace std;

int main() {
    // clear the window
    cout << "\033[2J\033[1;1H";


    cout << "Welcome to the Cache Simulator!" << endl;

    // Simulator Setup

    size_t numKBCache = 0;
    while (true) {
        cout << "How many KB is the cache for the simulation? (no more than 5): ";
        cin >> numKBCache;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (numKBCache >= 1 && numKBCache <= 5) {
            break;
        }

        cout << "Cache size must be between 1 and 5 KB.\n";
    }

    size_t sizeBytesCacheBlocks = 0;
    while (true) {
        cout << "How big are the blocks in the cache? (in bytes): ";
        cin >> sizeBytesCacheBlocks;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (sizeBytesCacheBlocks == 0) {
            cout << "Block size must be greater than 0.\n";
            continue;
        }

        if (sizeBytesCacheBlocks > numKBCache * 1024) {
            cout << "Block size cannot exceed cache size.\n";
            continue;
        }

        if ((numKBCache * 1024) % sizeBytesCacheBlocks != 0) {
            cout << "Block size must evenly divide cache size.\n";
            continue;
        }

        break;
    }

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
            size_t clockSpeed;
            size_t hitTimeCycles;
            size_t writePenaltyCycles;
            size_t readPenaltyCycles;

            cout << "Change Clock Speed (nanoseconds)" << endl;
            cin >> clockSpeed;
            simulationStats.setClockSpeed(clockSpeed);
            cout << "Change Hit Time (cycles)" << endl;
            cin >> hitTimeCycles;
            simulationStats.setHitTimeCycles(hitTimeCycles);
            cout << "Change Write Penalty Time (cycles)" << endl;
            cin >> writePenaltyCycles;
            simulationStats.setWritePenaltyCycles(writePenaltyCycles);
            cout << "Change Read Penalty Time (cycles)" << endl;
            cin >> readPenaltyCycles;
            simulationStats.setReadPenaltyCycles(readPenaltyCycles);

            cout << endl << "NEW SIMULATION STATS" << endl;
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

    string folderName = "Simulation_Results";

    // create the directory just in case it doesn't exist
    if (!fs::exists(folderName)) {
        fs::create_directory(folderName);
        cout << "CREATED SIMULATION RESULTS FOLDER" << endl;
    }

    // create visualization files for the user

    ofstream cacheStream;
    cacheStream.open(folderName + "/cache.txt", ios::out | ios::trunc);

    ofstream dataMemoryStream;
    dataMemoryStream.open(folderName + "/dataMemory.txt", ios::out | ios::trunc);

    try {
        if (!cacheStream || !dataMemoryStream) {
            throw runtime_error("Unable to open file");
        }

        cache.visualizeCache(cacheStream);
        dataMemory.visualizeDataMemory(dataMemoryStream, cache);

        cacheStream.close();
        dataMemoryStream.close();
    }
    catch (const exception &e) {
        cerr << "CRITICAL FILE PATHING ERROR: " << e.what() << endl;
    }

    cout << "CREATED VISUALIZATION FILES INSIDE: " << folderName << endl;
    cout << "PATH: " << fs::absolute(folderName).string() << endl;


    // implement cache and data memory interactions

    this_thread::sleep_for(chrono::seconds(5));

    /*
     * Here's the rundown: There will be reading and writing instructions being run (that's all it can do anyway)
     * This will be indicated with the keyword READ or WRITE.
     * You are reading/writing to a certain memory address so a normal simulation instruction would look like this:
     * WRITE [MEMORY ADDRESS] or READ [MEMORY ADDRESS]
     * The read and write keywords are very important so spelling them wrong warrants a retype (emulating a correct compiler)
     * At the end of simulation, the keyword QUIT can be used to exist the simulation
     */

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // clearing the window
    cout << "\033[2J\033[1;1H";

    ofstream resultStream;
    resultStream.open(folderName + "/simulation_results.txt");

    // get the file text header

    resultStream << "INSTRUCTIONS RAN" << endl << endl;

    // keep the loop running unless there is a break
    while (true) {
        string instruction;
        string commandWord;
        size_t memoryAddress;

        cout << "INSTRUCTION " << simulationStats.totalAccesses << ": ";
        getline(cin, instruction);
        stringstream ss(instruction);
        ss >> commandWord;

        bool cacheHit;
        // case of a read instruction
        if (commandWord == "READ") {
            // read in the memory address from the ss
            if (!(ss >> memoryAddress)) {
                cout << "INVALID MEMORY ADDRESS FORMAT" << endl;
                continue;
            }

            // check for invalid memory address
            if (memoryAddress >= dataMemory.memSize) {
                cout << "INVALID MEMORY ACCESS" << endl;
                continue;
            }
            // output the instruction to the simulation results text file
            resultStream << commandWord << " " << memoryAddress;

            // access!
            cacheHit = cache.access(dataMemory, memoryAddress, simulationStats, false);

            // update files and visualization in event of a hit or miss
            if (cacheHit) {
                resultStream << " [HIT]" << endl;
            }
            else {
                resultStream << " [MISS]" << endl;
            }
        }

        // case of a write instruction
        else if (commandWord == "WRITE") {
            // read in the memory address from the ss
            if (!(ss >> memoryAddress)) {
                cout << "INVALID MEMORY ADDRESS FORMAT" << endl;
                continue;
            }

            // check for invalid memory address
            if (memoryAddress >= dataMemory.memSize) {
                cout << "INVALID MEMORY ACCESS" << endl;
                continue;
            }
            // output the instruction to the simulation results text file
            resultStream << commandWord << " " << memoryAddress;

            // access!
            cacheHit = cache.access(dataMemory, memoryAddress, simulationStats, true);

            // update files and visualization in event of a hit or miss
            if (cacheHit) {
                resultStream << " [HIT]" << endl;
            }
            else {
                resultStream << " [MISS]" << endl;
            }
        }

        // case of an exit
        else if (commandWord == "QUIT") {
            cout << "EXITING SIMULATION!" << endl;
            break;
        }

        // case of bad instruction (command word)
        else {
            cout << "INVALID INSTRUCTION" << endl;
        }
        // update the text files
        cacheStream.open(folderName + "/cache.txt", ios::trunc);
        dataMemoryStream.open(folderName + "/dataMemory.txt", ios::trunc);

        if (cacheStream.is_open() && dataMemoryStream.is_open()) {
            cache.visualizeCache(cacheStream);
            dataMemory.visualizeDataMemory(dataMemoryStream, cache);

            cacheStream.close();
            dataMemoryStream.close();
        }
    }
    cout << endl << "Simulation Done, printing simulation results" << endl;

    resultStream << endl << "SIMULATION STATISTICS" << endl << endl;
    simulationStats.printStats(resultStream);

    this_thread::sleep_for(chrono::seconds(5));

    cacheStream.close();
    dataMemoryStream.close();
    resultStream.close();

    return 0;
}
