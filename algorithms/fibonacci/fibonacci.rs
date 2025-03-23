//! Fibonacci implementations in Rust.
//!
//! This file contains both recursive and iterative implementations of the
//! Fibonacci sequence calculation.

/// Calculate the nth Fibonacci number recursively.
///
/// # Arguments
///
/// * `n` - A non-negative integer
///
/// # Returns
///
/// The nth number in the Fibonacci sequence
///
/// # Note
///
/// This implementation is simple but inefficient for large values of n
/// due to redundant calculations. Time complexity is O(2^n).
pub fn fibonacci_recursive(n: u32) -> u64 {
    match n {
        0 => 0,
        1 => 1,
        _ => fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2),
    }
}

/// Calculate the nth Fibonacci number iteratively.
///
/// # Arguments
///
/// * `n` - A non-negative integer
///
/// # Returns
///
/// The nth number in the Fibonacci sequence
///
/// # Note
///
/// This implementation is more efficient with O(n) time complexity
/// and O(1) space complexity.
pub fn fibonacci_iterative(n: u32) -> u64 {
    match n {
        0 => 0,
        1 => 1,
        _ => {
            let mut a = 0;
            let mut b = 1;
            
            for _ in 2..=n {
                let temp = a + b;
                a = b;
                b = temp;
            }
            
            b
        }
    }
}

/// Calculate the nth Fibonacci number using memoization.
///
/// # Arguments
///
/// * `n` - A non-negative integer
/// * `memo` - Optional memoization cache
///
/// # Returns
///
/// The nth number in the Fibonacci sequence
///
/// # Note
///
/// This implementation combines recursion with memoization for
/// improved performance. Time complexity is O(n).
pub fn fibonacci_optimized(n: u32) -> u64 {
    fn fib_memo(n: u32, memo: &mut std::collections::HashMap<u32, u64>) -> u64 {
        if let Some(&result) = memo.get(&n) {
            return result;
        }
        
        let result = match n {
            0 => 0,
            1 => 1,
            _ => fib_memo(n - 1, memo) + fib_memo(n - 2, memo),
        };
        
        memo.insert(n, result);
        result
    }
    
    fib_memo(n, &mut std::collections::HashMap::new())
}

fn main() {
    // Test cases
    let test_cases = [0, 1, 2, 5, 10, 20, 30, 40];
    
    println!("Testing recursive implementation:");
    for &n in test_cases.iter().filter(|&&n| n <= 40) {
        let start = std::time::Instant::now();
        let result = fibonacci_recursive(n);
        let duration = start.elapsed();
        
        println!("fibonacci_recursive({}) = {} (took {:?})", n, result, duration);
    }
    
    println!("\nTesting iterative implementation:");
    for &n in &test_cases {
        let start = std::time::Instant::now();
        let result = fibonacci_iterative(n);
        let duration = start.elapsed();
        
        println!("fibonacci_iterative({}) = {} (took {:?})", n, result, duration);
    }
    
    println!("\nTesting optimized implementation:");
    for &n in &test_cases {
        let start = std::time::Instant::now();
        let result = fibonacci_optimized(n);
        let duration = start.elapsed();
        
        println!("fibonacci_optimized({}) = {} (took {:?})", n, result, duration);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_fibonacci_recursive() {
        let test_cases = [
            (0, 0),
            (1, 1),
            (2, 1),
            (3, 2),
            (4, 3),
            (5, 5),
            (10, 55),
        ];
        
        for &(n, expected) in &test_cases {
            assert_eq!(fibonacci_recursive(n), expected);
        }
    }
    
    #[test]
    fn test_fibonacci_iterative() {
        let test_cases = [
            (0, 0),
            (1, 1),
            (2, 1),
            (3, 2),
            (4, 3),
            (5, 5),
            (10, 55),
            (20, 6765),
            (30, 832040),
            (40, 102334155),
        ];
        
        for &(n, expected) in &test_cases {
            assert_eq!(fibonacci_iterative(n), expected);
        }
    }
    
    #[test]
    fn test_fibonacci_optimized() {
        let test_cases = [
            (0, 0),
            (1, 1),
            (2, 1),
            (3, 2),
            (4, 3),
            (5, 5),
            (10, 55),
            (20, 6765),
            (30, 832040),
            (40, 102334155),
        ];
        
        for &(n, expected) in &test_cases {
            assert_eq!(fibonacci_optimized(n), expected);
        }
    }
} 