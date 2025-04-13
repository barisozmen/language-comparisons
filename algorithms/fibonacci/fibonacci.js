function fibonacciRecursive(n) {
  if (n <= 1) {
    return n;
  }
  return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}


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


function fibonacciMemoized(n, memo = {}) {
  if (n in memo) {
    return memo[n];
  }
  
  if (n <= 1) {
    return n;
  }
  
  memo[n] = fibonacciMemoized(n - 1, memo) + fibonacciMemoized(n - 2, memo);
  return memo[n];
}

// Export functions for testing
if (typeof module !== 'undefined' && module.exports) {
  module.exports = {
    fibonacciRecursive,
    fibonacciIterative,
    fibonacciMemoized
  };
}