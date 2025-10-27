# Conway's Game of Life

This directory contains implementations of Conway's Game of Life in various programming languages.

## Algorithm Description

Conway's Game of Life is a cellular automaton with simple rules:
1. Any live cell with 2-3 neighbors survives
2. Any dead cell with exactly 3 neighbors becomes alive
3. All other cells die or stay dead

## Implementation Approach

Inspired by Peter Norvig's elegant style, these implementations:
- Store only **live cells** (not the entire grid) for efficiency
- Use sets/hash tables for O(1) lookup
- Consider only cells that could change (live cells and their neighbors)
- Apply rules functionally to compute the next generation

This approach is more efficient than storing a full 2D array, especially for sparse patterns.

## Language-Specific Notes

### Python
Uses set comprehensions and functional style for maximum elegance.

### Ruby
Leverages Ruby's expressive set operations and blocks.

### JavaScript
Uses Set and functional array methods.

### C++
Uses `std::unordered_set` with custom hash for pairs.

### C
Manual hash table implementation for efficiency.

### Rust
Uses `HashSet` with ownership patterns.

### Scheme
Functional approach with list operations.

## Common Test Pattern: Blinker

All implementations can be tested with a simple blinker pattern:
```
Generation 0:    Generation 1:
   ###              #
                    #
                    #
```

## Benchmarking Results

Performance results will be added after benchmarking.
