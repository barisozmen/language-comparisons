#!/bin/bash
# Master benchmark script for all graph algorithms

echo "╔══════════════════════════════════════════════════════╗"
echo "║  Graph Algorithms Cross-Language Benchmark Suite    ║"
echo "║  Inspired by Peter Norvig's Elegant Simplicity      ║"
echo "╚══════════════════════════════════════════════════════╝"
echo

cd "$(dirname "$0")"

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "  BFS (Breadth-First Search)"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
cd bfs/run
./benchmark.sh
cd ../..
echo

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "  DFS (Depth-First Search)"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
cd dfs/run
./benchmark.sh
cd ../..
echo

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "  Dijkstra (Shortest Path)"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
cd dijkstra/run
./benchmark.sh
cd ../..
echo

echo "╔══════════════════════════════════════════════════════╗"
echo "║  All benchmarks complete!                            ║"
echo "╚══════════════════════════════════════════════════════╝"

