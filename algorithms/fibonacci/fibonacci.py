"""
Fibonacci implementations in Python.

This file contains both recursive and iterative implementations of the 
Fibonacci sequence calculation.
"""

def fibonacci_recursive(n):
    """
    Calculate the nth Fibonacci number recursively.
    
    Args:
        n: A non-negative integer
        
    Returns:
        The nth number in the Fibonacci sequence
    
    Note:
        This implementation is simple but inefficient for large values of n
        due to redundant calculations. Time complexity is O(2^n).
    """
    if n <= 1:
        return n
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)


def fibonacci_iterative(n):
    """
    Calculate the nth Fibonacci number iteratively.
    
    Args:
        n: A non-negative integer
        
    Returns:
        The nth number in the Fibonacci sequence
    
    Note:
        This implementation is more efficient with O(n) time complexity
        and O(1) space complexity.
    """
    if n <= 1:
        return n
        
    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b


def fibonacci_optimized(n, memo={}):
    """
    Calculate the nth Fibonacci number using memoization.
    
    Args:
        n: A non-negative integer
        memo: Dictionary for memoization
        
    Returns:
        The nth number in the Fibonacci sequence
    
    Note:
        This implementation combines recursion with memoization for
        improved performance. Time complexity is O(n).
    """
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
        
    memo[n] = fibonacci_optimized(n - 1, memo) + fibonacci_optimized(n - 2, memo)
    return memo[n]


if __name__ == "__main__":
    # Test the implementations
    test_cases = [0, 1, 2, 5, 10, 20]
    
    print("Testing recursive implementation:")
    for n in test_cases:
        print(f"fibonacci_recursive({n}) = {fibonacci_recursive(n)}")
    
    print("\nTesting iterative implementation:")
    for n in test_cases:
        print(f"fibonacci_iterative({n}) = {fibonacci_iterative(n)}")
    
    print("\nTesting optimized implementation:")
    for n in test_cases:
        print(f"fibonacci_optimized({n}) = {fibonacci_optimized(n)}") 