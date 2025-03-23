/**
 * Fibonacci implementations in JavaScript.
 * 
 * This file contains both recursive and iterative implementations of the
 * Fibonacci sequence calculation.
 */

/**
 * Calculate the nth Fibonacci number recursively.
 * 
 * @param {number} n - A non-negative integer
 * @returns {number} The nth number in the Fibonacci sequence
 * 
 * Note: This implementation is simple but inefficient for large values of n
 * due to redundant calculations. Time complexity is O(2^n).
 */
function fibonacciRecursive(n) {
  if (n <= 1) {
    return n;
  }
  return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

/**
 * Calculate the nth Fibonacci number iteratively.
 * 
 * @param {number} n - A non-negative integer
 * @returns {number} The nth number in the Fibonacci sequence
 * 
 * Note: This implementation is more efficient with O(n) time complexity
 * and O(1) space complexity.
 */
function fibonacciIterative(n) {
  if (n <= 1) {
    return n;
  }
  
  let a = 0;
  let b = 1;
  
  for (let i = 2; i <= n; i++) {
    const temp = a + b;
    a = b;
    b = temp;
  }
  
  return b;
}

/**
 * Calculate the nth Fibonacci number using memoization.
 * 
 * @param {number} n - A non-negative integer
 * @param {Object} memo - Object for memoization
 * @returns {number} The nth number in the Fibonacci sequence
 * 
 * Note: This implementation combines recursion with memoization for
 * improved performance. Time complexity is O(n).
 */
function fibonacciOptimized(n, memo = {}) {
  if (n in memo) {
    return memo[n];
  }
  
  if (n <= 1) {
    return n;
  }
  
  memo[n] = fibonacciOptimized(n - 1, memo) + fibonacciOptimized(n - 2, memo);
  return memo[n];
}

// Export functions for testing
if (typeof module !== 'undefined' && module.exports) {
  module.exports = {
    fibonacciRecursive,
    fibonacciIterative,
    fibonacciOptimized
  };
}

// Test the implementations if run directly
if (require.main === module) {
  const testCases = [0, 1, 2, 5, 10, 20];
  
  console.log("Testing recursive implementation:");
  for (const n of testCases) {
    console.log(`fibonacciRecursive(${n}) = ${fibonacciRecursive(n)}`);
  }
  
  console.log("\nTesting iterative implementation:");
  for (const n of testCases) {
    console.log(`fibonacciIterative(${n}) = ${fibonacciIterative(n)}`);
  }
  
  console.log("\nTesting optimized implementation:");
  for (const n of testCases) {
    console.log(`fibonacciOptimized(${n}) = ${fibonacciOptimized(n)}`);
  }
} 