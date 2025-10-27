# Dijkstra's Algorithm

*"The question of whether a computer can think is no more interesting than the question of whether a submarine can swim."* - Dijkstra

## Overview

Dijkstra finds shortest paths in weighted graphs with non-negative edges. Greedy choice + optimal substructure = guaranteed correctness.

## Lines of Code

```bash
❯ loc .
--------------------------------------------------------------------------------
 Language             Files        Lines        Blank      Comment         Code
--------------------------------------------------------------------------------
 C++                      1          129           28            1          100
 C                        1          128           29            2           97
 Rust                     1          113           24            1           88
 Lisp                     1           88            6            1           81
 JavaScript               1          106           25            1           80
 Ruby                     1           90           21            1           68
 Python                   1           81           23            2           56
--------------------------------------------------------------------------------
 Total                    7          735          156            9          570
```

## Implementation Variants

**Heap-based**: O((V + E) log V) with priority queue  
**Array-based**: O(V²), simpler but slower  
**All-paths**: Single source to all destinations

## Key Insights

**Python (56 LOC)**: `heapq` makes priority queues trivial  
**Ruby (68 LOC)**: Manual heap simulation, still readable  
**JavaScript/Lisp (80-81 LOC)**: Array sorting as heap substitute  
**Rust (88 LOC)**: BinaryHeap with custom Ord trait  
**C/C++ (97-100 LOC)**: Priority queue or manual arrays

The 1.8:1 ratio shows heap abstraction dominates complexity. Without built-in heaps, all languages converge.

