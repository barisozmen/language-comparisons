#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

namespace language_comparison {

uint64_t FibonacciRecursive(int n) {
  if (n <= 1) {
    return n;
  }
  return FibonacciRecursive(n - 1) + FibonacciRecursive(n - 2);
}

uint64_t FibonacciIterative(int n) {
  if (n <= 1) {
    return n;
  }
  
  uint64_t a = 0;
  uint64_t b = 1;
  
  for (int i = 2; i <= n; ++i) {
    uint64_t temp = a + b;
    a = b;
    b = temp;
  }
  
  return b;
}

uint64_t FibonacciMemoization(int n, std::unordered_map<int, uint64_t>& memo) {
  if (memo.find(n) != memo.end()) {
    return memo[n];
  }
  
  if (n <= 1) {
    return n;
  }
  
  memo[n] = FibonacciMemoization(n - 1, memo) + FibonacciMemoization(n - 2, memo);
  return memo[n];
}

uint64_t FibonacciOptimized(int n) {
  std::unordered_map<int, uint64_t> memo;
  return FibonacciMemoization(n, memo);
}

} // namespace language_comparison