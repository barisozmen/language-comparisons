#!/bin/bash
# DFS Benchmark Runner

echo "=== DFS Algorithm Benchmark ==="
echo

echo "Python:"
time python3 run.py 2>&1 | head -2
echo

echo "Ruby:"
time ruby run.rb 2>&1 | head -2
echo

echo "JavaScript:"
time node run.js 2>&1 | head -2
echo

echo "=== Benchmark Complete ==="

