# Cache Simulator

A configurable direct-mapped cache simulator written in C++ that emulates cache behavior with detailed performance metrics and visualization.

## Features

- **Configurable Cache Parameters**
  - Cache size (up to 5 KB)
  - Block size (in bytes)
  - Direct-mapped architecture with LRU replacement

- **Write-Back Mechanism**
  - Dirty bit tracking for modified cache lines
  - Minimizes memory write operations

- **Interactive Simulation**
  - Real-time READ/WRITE instruction execution
  - Live cache and memory state visualization
  - Configurable timing parameters (clock speed, hit time, miss penalties)

- **Performance Analysis**
  - Hit/Miss rate tracking
  - Average Memory Access Time (AMAT) calculation
  - Total simulation cycles and time
  - Detailed instruction trace logging

## How It Works

The simulator creates a direct-mapped cache and main memory, then processes memory access instructions:

1. **Setup Phase**: Configure cache size, block size, and timing parameters
2. **Simulation Phase**: Execute READ/WRITE instructions to memory addresses
3. **Results**: View detailed statistics and visualizations

### Cache Access Flow
- **Cache Hit**: Data found in cache → fast access
- **Cache Miss**: Data not in cache → fetch from memory (+ write-back if dirty)
- **Write-Back**: Modified cache lines written to memory on eviction

## Running the Simulator

Run the cache simulator executable from any directory on your computer. The program will automatically create a `Simulation_Results` folder in the same directory where you launch it.

**Setup Process:**
1. Launch `./cache_simulator` from your terminal
2. Configure cache parameters (size, block size, timing)
3. Once setup is complete, the simulator will create the `Simulation_Results` folder and display its absolute path

**For the Best Experience:**
- Open `Simulation_Results/cache.txt` and `Simulation_Results/dataMemory.txt` in separate windows
- Keep these files visible alongside your terminal (multi-monitor setup works great!)
- Watch the cache and memory states update in real-time after each instruction
- The simulator will guide you on where to find the output files

**After Simulation:**
- Check `simulation_results.txt` for a complete instruction trace and performance statistics
- Review hit/miss rates, AMAT, and total cycle counts to analyze your memory access patterns

## Usage

### Interactive Commands

During simulation, enter instructions in the following format:
```
READ [memory_address]   # Read from memory address
WRITE [memory_address]  # Write to memory address
QUIT                    # Exit simulation
```

### Example Session
```
INSTRUCTION 0: READ 4
INSTRUCTION 1: WRITE 4
INSTRUCTION 2: READ 8
INSTRUCTION 3: WRITE 1028
INSTRUCTION 4: READ 4
INSTRUCTION 5: QUIT
```

## Output Files

The simulator generates visualization files in `Simulation_Results/`:

- **cache.txt**: Current cache state with tags, valid/dirty bits, and data
- **dataMemory.txt**: Main memory contents organized by blocks
- **simulation_results.txt**: Instruction trace and performance statistics

### Sample Output

**Cache Visualization:**
```
Block Size: 4 bytes
Number of Cache Lines: 256

Index 1
Tag (in Base 10): 0 | Valid: 1 | Dirty: 0
Offsets |0 |1 |2 |3 |
Data    |* |U |M |E |
```

**Performance Statistics:**
```
Total accesses: 5 accesses
Hits per access: 20%
Misses per access: 80%
AMAT: 41 cycles
Total Simulation Cycles: 305 cycles
Simulation Time: 305 ns
```

## Performance Metrics

- **Hit Rate**: Percentage of accesses found in cache
- **Miss Rate**: Percentage of accesses requiring memory fetch
- **AMAT**: Average Memory Access Time in cycles
- **Total Cycles**: Complete simulation cycle count

## Configuration Options

Customize timing parameters during setup:
- Clock speed (nanoseconds)
- Hit time (cycles)
- Read penalty (cycles)
- Write penalty (cycles)

## Technical Details

- **Architecture**: Direct-mapped cache with configurable block size
- **Replacement Policy**: LRU (Least Recently Used)
- **Write Policy**: Write-back with dirty bit tracking
- **Address Mapping**: Tag-Index-Offset decomposition

## Project Structure
```
cache_simulator/
├── main.cpp              # Driver program
├── cache.h/cpp           # Cache implementation
├── dataMem.h/cpp         # Data memory implementation
├── simulationStats.h/cpp # Performance tracking
└── Simulation_Results/   # Output directory
    ├── cache.txt
    ├── dataMemory.txt
    └── simulation_results.txt
```

## Requirements

- C++17 or later
- Standard library support for `<filesystem>`

## Author

Oluwatosin Ojo
