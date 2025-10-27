#!/bin/bash
# BFS Benchmark Runner

echo "=== BFS Algorithm Benchmark ==="
echo

# Python
echo "Python:"
time python3 run.py 2>&1 | head -2
echo

# Ruby
echo "Ruby:"
time ruby run.rb 2>&1 | head -2
echo

# JavaScript
echo "JavaScript:"
time node run.js 2>&1 | head -2
echo

# C (compile first)
echo "C:"
gcc run.c -o run_c -O2 2>/dev/null
time ./run_c 2>&1 | head -2
rm -f run_c
echo

# C++ (compile first)
echo "C++:"
g++ -std=c++17 run.cpp -o run_cpp -O2 2>/dev/null
time ./run_cpp 2>&1 | head -2
rm -f run_cpp
echo

# Rust (compile first)
echo "Rust:"
rustc run.rs -o run_rs -O 2>/dev/null && time ./run_rs 2>&1 | head -2 && rm -f run_rs || echo "Rust requires serde_json dependency"
echo

echo "=== Benchmark Complete ==="

