# Makefile for Virtual Memory Programming Exercises
# Chapter 10: Virtual Memory Solutions

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
DEBUG_FLAGS = -g -DDEBUG

# Executable names
EXERCISE1 = exercise1_page_table
EXERCISE2 = exercise2_fifo
EXERCISE3 = exercise3_lru
EXERCISE4 = exercise4_working_set
EXERCISE5 = exercise5_tlb
EXERCISE6 = exercise6_memory_mapped
EXERCISE7 = exercise7_buddy_system
EXERCISE8 = exercise8_optimal

# All executables
EXECUTABLES = $(EXERCISE1) $(EXERCISE2) $(EXERCISE3) $(EXERCISE4) \
              $(EXERCISE5) $(EXERCISE6) $(EXERCISE7) $(EXERCISE8)

# Default target: build all
all: $(EXECUTABLES)
	@echo "All exercises compiled successfully!"
	@echo "Run any program with: ./exercise<number>_<name>"

# Individual targets
$(EXERCISE1): exercise1_page_table.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "Compiled: $@"

$(EXERCISE2): exercise2_fifo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "Compiled: $@"

$(EXERCISE3): exercise3_lru.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "Compiled: $@"

$(EXERCISE4): exercise4_working_set.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "Compiled: $@"

$(EXERCISE5): exercise5_tlb.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "Compiled: $@"

$(EXERCISE6): exercise6_memory_mapped.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "Compiled: $@"

$(EXERCISE7): exercise7_buddy_system.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "Compiled: $@"

$(EXERCISE8): exercise8_optimal.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "Compiled: $@"

# Compile with debug symbols
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all
	@echo "Debug builds complete!"

# Clean build artifacts
clean:
	rm -f $(EXECUTABLES)
	@echo "Cleaned all executables"

# Run all tests
test: all
	@echo "Running all exercises..."
	@echo "\n=== Exercise 1: Page Table ==="
	@./$(EXERCISE1) | head -n 30
	@echo "\n=== Exercise 2: FIFO ==="
	@./$(EXERCISE2) | head -n 30
	@echo "\n=== Exercise 3: LRU ==="
	@./$(EXERCISE3) | head -n 30
	@echo "\n=== Exercise 4: Working Set ==="
	@./$(EXERCISE4) | head -n 30
	@echo "\n=== Exercise 5: TLB ==="
	@./$(EXERCISE5) | head -n 30
	@echo "\n=== Exercise 6: Memory-Mapped Files ==="
	@./$(EXERCISE6) | head -n 30
	@echo "\n=== Exercise 7: Buddy System ==="
	@./$(EXERCISE7) | head -n 30
	@echo "\n=== Exercise 8: Optimal ==="
	@./$(EXERCISE8) | head -n 30
	@echo "\nAll tests complete!"

# Individual exercise shortcuts
exercise1: $(EXERCISE1)
exercise2: $(EXERCISE2)
exercise3: $(EXERCISE3)
exercise4: $(EXERCISE4)
exercise5: $(EXERCISE5)
exercise6: $(EXERCISE6)
exercise7: $(EXERCISE7)
exercise8: $(EXERCISE8)

# Run individual exercises
run1: $(EXERCISE1)
	./$(EXERCISE1)

run2: $(EXERCISE2)
	./$(EXERCISE2)

run3: $(EXERCISE3)
	./$(EXERCISE3)

run4: $(EXERCISE4)
	./$(EXERCISE4)

run5: $(EXERCISE5)
	./$(EXERCISE5)

run6: $(EXERCISE6)
	./$(EXERCISE6)

run7: $(EXERCISE7)
	./$(EXERCISE7)

run8: $(EXERCISE8)
	./$(EXERCISE8)

# Help target
help:
	@echo "Virtual Memory Exercises - Makefile Help"
	@echo "========================================"
	@echo ""
	@echo "Available targets:"
	@echo "  make all        - Compile all exercises (default)"
	@echo "  make clean      - Remove all executables"
	@echo "  make debug      - Compile with debug symbols"
	@echo "  make test       - Run all exercises (first 30 lines)"
	@echo ""
	@echo "Individual compilation:"
	@echo "  make exercise1  - Page Table Simulator"
	@echo "  make exercise2  - FIFO Page Replacement"
	@echo "  make exercise3  - LRU Page Replacement"
	@echo "  make exercise4  - Working Set Simulator"
	@echo "  make exercise5  - TLB Simulator"
	@echo "  make exercise6  - Memory-Mapped Files"
	@echo "  make exercise7  - Buddy System"
	@echo "  make exercise8  - Optimal Page Replacement"
	@echo ""
	@echo "Run individual exercises:"
	@echo "  make run1       - Run Exercise 1"
	@echo "  make run2       - Run Exercise 2"
	@echo "  make run3       - Run Exercise 3"
	@echo "  make run4       - Run Exercise 4"
	@echo "  make run5       - Run Exercise 5"
	@echo "  make run6       - Run Exercise 6"
	@echo "  make run7       - Run Exercise 7"
	@echo "  make run8       - Run Exercise 8"
	@echo ""
	@echo "Examples:"
	@echo "  make            - Compile everything"
	@echo "  make exercise3  - Compile only LRU exercise"
	@echo "  make run3       - Compile and run LRU exercise"
	@echo "  make clean all  - Clean and rebuild everything"

# Phony targets
.PHONY: all clean debug test help \
        exercise1 exercise2 exercise3 exercise4 \
        exercise5 exercise6 exercise7 exercise8 \
        run1 run2 run3 run4 run5 run6 run7 run8
