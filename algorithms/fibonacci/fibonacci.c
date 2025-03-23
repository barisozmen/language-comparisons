/**
 * Fibonacci implementations in C.
 *
 * This file contains both recursive and iterative implementations of the
 * Fibonacci sequence calculation.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Calculate the nth Fibonacci number recursively.
 *
 * @param n A non-negative integer
 * @return The nth number in the Fibonacci sequence
 *
 * Note: This implementation is simple but inefficient for large values of n
 * due to redundant calculations. Time complexity is O(2^n).
 */
unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
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
unsigned long long fibonacci_iterative(int n) {
    if (n <= 1) {
        return n;
    }
    
    unsigned long long a = 0;
    unsigned long long b = 1;
    unsigned long long temp;
    
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    
    return b;
}

/**
 * Calculate the nth Fibonacci number using dynamic programming.
 *
 * @param n A non-negative integer
 * @return The nth number in the Fibonacci sequence
 *
 * Note: This implementation uses an array to store previous results,
 * achieving O(n) time complexity and O(n) space complexity.
 */
unsigned long long fibonacci_dynamic(int n) {
    if (n <= 1) {
        return n;
    }
    
    unsigned long long* fib = (unsigned long long*)malloc((n + 1) * sizeof(unsigned long long));
    if (fib == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    fib[0] = 0;
    fib[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    
    unsigned long long result = fib[n];
    free(fib);
    
    return result;
}

int main() {
    // Test cases
    int test_cases[] = {0, 1, 2, 5, 10, 20, 30, 40};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("Testing recursive implementation:\n");
    for (int i = 0; i < num_tests && test_cases[i] <= 40; i++) {
        // Skip larger values for recursive implementation
        if (test_cases[i] > 40) continue;
        printf("fibonacci_recursive(%d) = %llu\n", 
               test_cases[i], fibonacci_recursive(test_cases[i]));
    }
    
    printf("\nTesting iterative implementation:\n");
    for (int i = 0; i < num_tests; i++) {
        printf("fibonacci_iterative(%d) = %llu\n", 
               test_cases[i], fibonacci_iterative(test_cases[i]));
    }
    
    printf("\nTesting dynamic programming implementation:\n");
    for (int i = 0; i < num_tests; i++) {
        printf("fibonacci_dynamic(%d) = %llu\n", 
               test_cases[i], fibonacci_dynamic(test_cases[i]));
    }
    
    return 0;
} 