/**
 * Tests for Fibonacci algorithm implementations in C++.
 */

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <cassert>

// Declaration of functions from fibonacci.cpp
namespace language_comparison {
  uint64_t FibonacciRecursive(int n);
  uint64_t FibonacciIterative(int n);
  uint64_t FibonacciOptimized(int n);
}

// Test structure
struct TestCase {
  int input;
  uint64_t expected;
};

// Simple test framework
template<typename Func>
bool RunTestSuite(const std::string& name, Func func, 
                 const std::vector<TestCase>& test_cases, int max_n) {
  std::cout << "Testing " << name << ":\n";
  bool all_passed = true;
  
  for (const auto& test : test_cases) {
    if (test.input > max_n) {
      std::cout << "  Skipping test case " << test.input 
                << " (too large for this implementation)\n";
      continue;
    }
    
    uint64_t result = func(test.input);
    bool passed = result == test.expected;
    
    std::cout << "  " << name << "(" << test.input << ") = " << result 
              << ", expected: " << test.expected 
              << " - " << (passed ? "PASS" : "FAIL") << "\n";
    
    if (!passed) {
      all_passed = false;
    }
  }
  
  return all_passed;
}

int main() {
  // Define test cases
  std::vector<TestCase> test_cases = {
    {0, 0},
    {1, 1},
    {2, 1},
    {3, 2},
    {4, 3},
    {5, 5},
    {10, 55},
    {20, 6765},
    {30, 832040},
    {40, 102334155}
  };
  
  bool recursive_passed = RunTestSuite("FibonacciRecursive", 
                                      language_comparison::FibonacciRecursive, 
                                      test_cases, 40);
  std::cout << "\n";
  
  bool iterative_passed = RunTestSuite("FibonacciIterative", 
                                      language_comparison::FibonacciIterative, 
                                      test_cases, 93);
  std::cout << "\n";
  
  bool optimized_passed = RunTestSuite("FibonacciOptimized", 
                                      language_comparison::FibonacciOptimized, 
                                      test_cases, 93);
  
  std::cout << "\nAll tests " 
            << ((recursive_passed && iterative_passed && optimized_passed) ? 
                "PASSED" : "FAILED") << "\n";
  
  return (recursive_passed && iterative_passed && optimized_passed) ? 0 : 1;
} 