/**
 * Tests for Fibonacci algorithm implementations in JavaScript.
 */
const { fibonacciRecursive, fibonacciIterative, fibonacciOptimized } = require('./fibonacci');

// Define test cases
const testCases = {
  0: 0,
  1: 1,
  2: 1,
  3: 2,
  4: 3,
  5: 5,
  10: 55,
  20: 6765,
  30: 832040
};

// Test recursive implementation
console.log("Testing fibonacci_recursive:");
let allPassed = true;
for (const [n, expected] of Object.entries(testCases)) {
  // Skip larger values for recursive implementation to avoid long execution time
  if (parseInt(n) > 15) continue;
  
  const result = fibonacciRecursive(parseInt(n));
  const passed = result === expected;
  console.log(`  fibonacciRecursive(${n}) = ${result}, expected: ${expected} - ${passed ? 'PASS' : 'FAIL'}`);
  if (!passed) allPassed = false;
}

// Test iterative implementation
console.log("\nTesting fibonacci_iterative:");
for (const [n, expected] of Object.entries(testCases)) {
  const result = fibonacciIterative(parseInt(n));
  const passed = result === expected;
  console.log(`  fibonacciIterative(${n}) = ${result}, expected: ${expected} - ${passed ? 'PASS' : 'FAIL'}`);
  if (!passed) allPassed = false;
}

// Test optimized implementation
console.log("\nTesting fibonacci_optimized:");
for (const [n, expected] of Object.entries(testCases)) {
  const result = fibonacciOptimized(parseInt(n));
  const passed = result === expected;
  console.log(`  fibonacciOptimized(${n}) = ${result}, expected: ${expected} - ${passed ? 'PASS' : 'FAIL'}`);
  if (!passed) allPassed = false;
}

console.log(`\nAll tests ${allPassed ? 'PASSED' : 'FAILED'}`);
process.exit(allPassed ? 0 : 1); 