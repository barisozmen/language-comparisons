# Depth-First Search

*"Simplicity is prerequisite for reliability."* - Dijkstra

## Overview

DFS explores as deep as possible before backtracking. Natural for recursion, efficient for topological sorts.

## Lines of Code

```bash
❯ loc .
--------------------------------------------------------------------------------
 Language             Files        Lines        Blank      Comment         Code
--------------------------------------------------------------------------------
 C                        1          143           30            1          112
 C++                      1          119           26            1           92
 Rust                     1           96           21            1           74
 Lisp                     1           64            6            1           57
 Python                   1           60           19            1           40
 JavaScript               1           58           18            1           39
 Ruby                     1           51           16            1           34
--------------------------------------------------------------------------------
 Total                    7          591          136            7          448
```

## Implementation Variants

**Recursive**: Elegant, stack-limited, O(V + E) time  
**Iterative**: Explicit stack, no recursion limit  
**Postorder**: Children before parents, useful for cleanup

## Key Insights

**Ruby (34 LOC)**: Blocks and splat operators minimize boilerplate  
**JavaScript/Python (39-40 LOC)**: Native stacks and destructuring  
**Lisp (57 LOC)**: Tail recursion elegance  
**Rust (74 LOC)**: Mutable references require care  
**C++/C (92-112 LOC)**: Manual stack and backtracking logic

The 3.3:1 ratio reveals recursion's conceptual simplicity versus iterative control.

