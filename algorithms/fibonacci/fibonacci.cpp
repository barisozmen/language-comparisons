/**
 * Fibonacci implementations in C++.
 *
 * This file contains both recursive and iterative implementations of the
 * Fibonacci sequence calculation.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

namespace language_comparison {

/**
 * Calculate the nth Fibonacci number recursively.
 *
 * @param n A non-negative integer
 * @return The nth number in the Fibonacci sequence
 *
 * Note: This implementation is simple but inefficient for large values of n
 * due to redundant calculations. Time complexity is O(2^n).
 */
uint64_t FibonacciRecursive(int n) {
  if (n <= 1) {
    return n;
  }
  return FibonacciRecursive(n - 1) + FibonacciRecursive(n - 2);
}

/**
 * Calculate the nth Fibonacci number iteratively.
 *
 * @param n A non-negative integer
 * @return The nth number in the Fibonacci sequence
 *
 * Note: This implementation is more efficient with O(n) time complexity
 * and O(1) space complexity.
 */
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

/**
 * Calculate the nth Fibonacci number using memoization.
 *
 * @param n A non-negative integer
 * @param memo Unordered map for memoization
 * @return The nth number in the Fibonacci sequence
 *
 * Note: This implementation combines recursion with memoization for
 * improved performance. Time complexity is O(n).
 */
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

/**
 * Wrapper function for the memoized Fibonacci implementation.
 *
 * @param n A non-negative integer
 * @return The nth number in the Fibonacci sequence
 */
uint64_t FibonacciOptimized(int n) {
  std::unordered_map<int, uint64_t> memo;
  return FibonacciMemoization(n, memo);
}

} // namespace language_comparison

int main() {
  // Test cases
  std::vector<int> test_cases = {0, 1, 2, 5, 10, 20, 30, 40};
  
  std::cout << "Testing recursive implementation:" << std::endl;
  for (int n : test_cases) {
    if (n > 40) continue; // Skip larger values for recursive implementation
    
    auto start = std::chrono::high_resolution_clock::now();
    uint64_t result = language_comparison::FibonacciRecursive(n);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "FibonacciRecursive(" << n << ") = " << result 
              << " (took " << duration << " µs)" << std::endl;
  }
  
  std::cout << "\nTesting iterative implementation:" << std::endl;
  for (int n : test_cases) {
    auto start = std::chrono::high_resolution_clock::now();
    uint64_t result = language_comparison::FibonacciIterative(n);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "FibonacciIterative(" << n << ") = " << result 
              << " (took " << duration << " µs)" << std::endl;
  }
  
  std::cout << "\nTesting optimized implementation:" << std::endl;
  for (int n : test_cases) {
    auto start = std::chrono::high_resolution_clock::now();
    uint64_t result = language_comparison::FibonacciOptimized(n);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "FibonacciOptimized(" << n << ") = " << result 
              << " (took " << duration << " µs)" << std::endl;
  }
  
  return 0;
} 