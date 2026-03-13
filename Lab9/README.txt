# Virtual Memory Programming Exercises - Solutions

This directory contains complete solutions for all exercises from Chapter 10: Virtual Memory.

## Files Included

1. **exercise1_page_table.cpp** - Page Table Simulator
2. **exercise2_fifo.cpp** - FIFO Page Replacement Algorithm
3. **exercise3_lru.cpp** - LRU Page Replacement Algorithm
4. **exercise4_working_set.cpp** - Working Set Simulator
5. **exercise5_tlb.cpp** - TLB (Translation Lookaside Buffer) Simulator
6. **exercise6_memory_mapped.cpp** - Memory-Mapped File I/O
7. **exercise7_buddy_system.cpp** - Buddy System Memory Allocator
8. **exercise8_optimal.cpp** - Optimal Page Replacement Algorithm

## Compilation Instructions

### Compile All Programs
```bash
make all
```

### Compile Individual Programs
```bash
make exercise1    # Page Table Simulator
make exercise2    # FIFO Algorithm
make exercise3    # LRU Algorithm
make exercise4    # Working Set
make exercise5    # TLB Simulator
make exercise6    # Memory-Mapped Files
make exercise7    # Buddy System
make exercise8    # Optimal Algorithm
```

### Clean Build Files
```bash
make clean
```

## Running the Programs

After compilation, run each program:

```bash
./exercise1_page_table
./exercise2_fifo
./exercise3_lru
./exercise4_working_set
./exercise5_tlb
./exercise6_memory_mapped
./exercise7_buddy_system
./exercise8_optimal
```

## Program Descriptions

### Exercise 1: Page Table Simulator
- Implements a basic page table with virtual to physical address translation
- Features: valid bit, dirty bit, reference bit
- Demonstrates page faults and address translation
- **Key Concepts**: Virtual memory, page tables, address translation

### Exercise 2: FIFO Page Replacement
- First-In-First-Out page replacement algorithm
- Tracks page faults and displays frame states
- Demonstrates Belady's Anomaly
- **Key Concepts**: Page replacement, FIFO queue, page fault rates

### Exercise 3: LRU Page Replacement
- Least Recently Used algorithm with timestamp tracking
- Compares performance with FIFO
- Uses map for efficient last access time lookup
- **Key Concepts**: LRU replacement, temporal locality, counter-based implementation

### Exercise 4: Working Set Simulator
- Calculates working set at each time point
- Tracks working set size changes over time
- Visualizes memory requirements
- **Key Concepts**: Working set model, locality of reference, memory estimation

### Exercise 5: TLB Simulator
- Simulates Translation Lookaside Buffer with LRU replacement
- Calculates hit ratios and effective access times
- Demonstrates locality benefits
- **Key Concepts**: TLB, memory hierarchy, access time calculation

### Exercise 6: Memory-Mapped File I/O
- Simulates memory-mapped files with demand paging
- Compares with traditional file I/O
- Demonstrates locality of reference benefits
- **Key Concepts**: Memory-mapped I/O, demand paging, file access patterns

### Exercise 7: Buddy System Allocator
- Complete buddy system implementation
- Block splitting and merging
- Fragmentation analysis
- **Key Concepts**: Kernel memory allocation, buddy algorithm, fragmentation

### Exercise 8: Optimal Page Replacement
- Belady's optimal algorithm (theoretical best)
- Comprehensive comparison: Optimal vs LRU vs FIFO
- Demonstrates why optimal is theoretical
- **Key Concepts**: Optimal replacement, algorithm comparison, benchmarking

## Expected Output Examples

### Exercise 1 Output Sample:
```
=== Page Table Simulator ===
File initialized...
Page Size: 512 bytes
Number of Pages: 16

Translating Virtual Address: 1024
Page Number: 2, Offset: 0
Physical Address: 5120
```

### Exercise 2 Output Sample:
```
Reference: 7 | FAULT | Frames: [ 7 - -]
Reference: 0 | FAULT | Frames: [ 7 0 -]
Reference: 1 | FAULT | Frames: [ 7 0 1]
...
Total References: 13
Page Faults: 12
Page Fault Rate: 92.31%
```

### Exercise 3 Output Sample:
```
Reference: 7 (Time: 1) | FAULT | Frames: [ 7 - -]
...
=== Comparison Table ===
Algorithm          Page Faults    Difference
LRU               10             -
FIFO              12             2
LRU performs better (fewer page faults)
```

## Learning Objectives

After completing these exercises, you should understand:

1. **Virtual Memory Fundamentals**
   - Address translation mechanisms
   - Page tables and their management
   - Valid/invalid bits and page faults

2. **Page Replacement Algorithms**
   - FIFO, LRU, and Optimal algorithms
   - Trade-offs between different strategies
   - Belady's Anomaly

3. **Memory Management**
   - Working set model
   - TLB operation and benefits
   - Buddy system allocation

4. **Performance Analysis**
   - Hit ratios and fault rates
   - Effective access time calculations
   - Fragmentation measurement

## Implementation Notes

### Data Structures Used
- **Vector**: For frames, page tables, reference strings
- **Queue**: For FIFO ordering
- **Map**: For LRU timestamps, page table mappings
- **Set**: For working set calculations

### Design Patterns
- **Object-Oriented Design**: Each simulator is a class
- **Encapsulation**: Private implementation details
- **Statistics Tracking**: Comprehensive metrics collection

### C++ Features Used
- STL containers (vector, map, queue, set)
- Iterator patterns
- Lambda functions (in some implementations)
- Object-oriented programming

## Testing Recommendations

1. **Test with provided reference strings** first to verify correctness
2. **Create your own test cases** to explore edge cases
3. **Compare results** between different algorithms
4. **Analyze performance** under different scenarios
5. **Experiment with parameters** (frame counts, page sizes, etc.)

## Common Issues and Solutions

### Compilation Errors
- Ensure C++11 or later: `g++ -std=c++11`
- Include all necessary headers
- Check for typos in file names

### Runtime Issues
- Verify reference strings are valid
- Check frame counts are positive
- Ensure sufficient memory for large tests

### Understanding Output
- Page faults are normal and expected
- Higher hit ratios are better
- Compare algorithms on same test cases

## Extensions and Improvements

Want to extend these programs? Try:

1. **Add Second-Chance (Clock) algorithm** to exercise 2
2. **Implement graphical output** for visualizations
3. **Add slab allocator** to exercise 7
4. **Create interactive menu system** for all programs
5. **Add file I/O** to load test cases from files
6. **Implement multi-threaded simulations**
7. **Add comprehensive test suites**

## References

- Operating System Concepts, 10th Edition (Silberschatz, Galvin, Gagne)
- Chapter 10: Virtual Memory
- Modern Operating Systems (Tanenbaum)

## Author Notes

These solutions demonstrate:
- Clean, readable code
- Comprehensive comments
- Professional output formatting
- Proper error handling
- Educational value with detailed explanations

Each solution is designed to be:
- **Self-contained**: Runs independently
- **Well-documented**: Extensive comments
- **Educational**: Clear demonstrations of concepts
- **Extensible**: Easy to modify and enhance

## License

These solutions are provided for educational purposes.
Feel free to use, modify, and learn from them!
