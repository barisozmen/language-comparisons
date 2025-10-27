# Graph Algorithms

*"The purpose of abstraction is not to be vague, but to create a new semantic level in which one can be absolutely precise."* - Dijkstra

## Overview

Three fundamental graph algorithms, each exploring different tradeoffs:
- **BFS**: Shortest paths in unweighted graphs (queue-based)
- **DFS**: Deep exploration, topological ordering (stack/recursion)  
- **Dijkstra**: Shortest paths in weighted graphs (priority queue)

Each algorithm implemented in multiple styles across 7 languages.

## Lines of Code

```bash
❯ loc .
--------------------------------------------------------------------------------
 Language             Files        Lines        Blank      Comment         Code
--------------------------------------------------------------------------------
 C                        3          394           87            5          302
 C++                      3          344           73            3          268
 Rust                     3          284           60            3          221
 Lisp                     3          222           17            3          202
 JavaScript               3          250           64            3          183
 Ruby                     3          218           53            3          162
 Python                   3          218           58            6          154
 Markdown                 4          136           38            0           98
--------------------------------------------------------------------------------
 Total                   25         2066          450           26         1590
```

## Algorithm Breakdown

| Algorithm | Python | Ruby | JS | Lisp | Rust | C++ | C |
|-----------|--------|------|----|----|------|-----|---|
| BFS | 58 | 60 | 64 | 64 | 59 | 76 | 93 |
| DFS | 40 | 34 | 39 | 57 | 74 | 92 | 112 |
| Dijkstra | 56 | 68 | 80 | 81 | 88 | 100 | 97 |
| **Total** | **154** | **162** | **183** | **202** | **221** | **268** | **302** |

## Key Insights

### Why Python is Shortest (154 LOC)
- `heapq` for priority queues (Dijkstra)
- `deque` for efficient queues (BFS)  
- List comprehensions eliminate loops
- Native set operations

### Why Ruby Excels at DFS (34 LOC)
- Blocks and procs create elegant recursion
- Splat operators (`*args`) minimize ceremony
- Set operations with natural syntax

### Why C is Longest (302 LOC)
- Manual queue/stack implementation
- Explicit string manipulation
- Array bounds checking
- No built-in priority queue

### The Data Structure Tax

Graph algorithms reveal language abstraction costs:
- **Queue**: 1.6x code increase without built-in (BFS)
- **Recursion**: 3.3x simpler than iterative (DFS)  
- **Heap**: 1.8x code savings with built-in (Dijkstra)

### Complexity vs Expressiveness

**2:1 ratio** (302:154) between C and Python shows:
- Data structure libraries matter more than syntax sugar
- Abstraction enables algorithm focus over implementation details
- Low-level control trades brevity for performance

## Running & Benchmarking

Each algorithm directory contains a `run/` folder with:
- `test_cases.json`: Shared test data across all languages
- `run.<ext>`: Test runners for each language
- `benchmark.sh`: Timing comparison script

```bash
# Run all benchmarks
./run_all_benchmarks.sh

# Run individual algorithm
cd bfs/run && ./benchmark.sh
```

## Implementation Patterns

Each algorithm directory contains:
- **Multiple approaches**: recursive, iterative, optimized
- **Consistent interface**: graph as adjacency list  
- **Working examples**: runnable test cases
- **Language idioms**: respecting each language's strengths

## Further Reading

- [Dijkstra (1959): "A Note on Two Problems in Connexion with Graphs"](https://www.cs.utexas.edu/users/EWD/ewd01xx/EWD135.PDF)
- [Tarjan (1972): "Depth-First Search and Linear Graph Algorithms"](https://epubs.siam.org/doi/10.1137/0201010)
- [Cormen et al.: "Introduction to Algorithms"](https://mitpress.mit.edu/books/introduction-algorithms-third-edition)

## Philosophy

Following Norvig's principle: *implement the simplest thing that could possibly work, then measure*. These algorithms are pedagogical first, optimized second. The goal is understanding, not benchmarking.
