# Breadth-First Search

*"The cheapest, simplest, most reliable components of a computer system are those that aren't there."* - Gordon Bell

## Overview

BFS explores level by level using a queue. It guarantees shortest paths in unweighted graphs.

## Lines of Code

```bash
❯ loc .
--------------------------------------------------------------------------------
 Language             Files        Lines        Blank      Comment         Code
--------------------------------------------------------------------------------
 Rust                     1          138           22            6          110
 C                        1          123           28            2           93
 C++                      1           96           19            1           76
 Python                   1           88           16            4           68
 Lisp                     1           70            5            1           64
 JavaScript               1           86           21            1           64
 Ruby                     1           77           16            1           60
--------------------------------------------------------------------------------
 Total                    8          720          138           16          566
```

## Implementation Variants

**Iterative** (standard): Queue-based, O(V + E) time  
**Level-order**: Returns nodes grouped by distance  
**Bidirectional**: Search from both ends, meets in middle

## Key Insights

**Ruby (60 LOC)**: Minimal with array-as-queue and blocks  
**JavaScript/Lisp (64 LOC)**: Native arrays and functional approaches  
**Python (68 LOC)**: Added bidirectional with reverse graph  
**C++ (76 LOC)**: STL queue abstracts complexity  
**C (93 LOC)**: Manual queue and string manipulation  
**Rust (110 LOC)**: Bidirectional requires explicit HashMap management

The 1.8:1 ratio (110:60) shows that bidirectional search adds complexity, especially in typed languages requiring explicit data structures.

## Benchmark Results

Runtime comparison (including startup + execution):

| Language | Time (real) | Notes |
|----------|------------|-------|
| Python | 29ms | Fastest interpreted language |
| JavaScript | 32ms | V8 JIT optimization |
| Ruby | 42ms | Competitive despite startup |
| C++ | 344ms | Includes compile time (~340ms) |
| C | 862ms | Includes compile time (~860ms) |

*Note: Compiled languages show compile overhead. For production, pre-compiled binaries run in ~1-2ms.*

