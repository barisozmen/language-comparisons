/**
 * Tests for Fibonacci algorithm implementations in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function declarations from fibonacci.c
unsigned long long fibonacci_recursive(int n);
unsigned long long fibonacci_iterative(int n);
unsigned long long fibonacci_dynamic(int n);

// Test structure
typedef struct {
    int input;
    unsigned long long expected;
} TestCase;

bool run_test_suite(const char* name, unsigned long long (*func)(int), TestCase* test_cases, int num_tests, int max_n) {
    printf("Testing %s:\n", name);
    bool all_passed = true;
    
    for (int i = 0; i < num_tests; i++) {
        if (test_cases[i].input > max_n) {
            printf("  Skipping test case %d (too large for this implementation)\n", 
                   test_cases[i].input);
            continue;
        }
        
        unsigned long long result = func(test_cases[i].input);
        bool passed = result == test_cases[i].expected;
        
        printf("  %s(%d) = %llu, expected: %llu - %s\n", 
               name, 
               test_cases[i].input, 
               result, 
               test_cases[i].expected, 
               passed ? "PASS" : "FAIL");
        
        if (!passed) {
            all_passed = false;
        }
    }
    
    return all_passed;
}

int main() {
    // Define test cases
    TestCase test_cases[] = {
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
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    bool recursive_passed = run_test_suite("fibonacci_recursive", fibonacci_recursive, test_cases, num_tests, 40);
    printf("\n");
    
    bool iterative_passed = run_test_suite("fibonacci_iterative", fibonacci_iterative, test_cases, num_tests, 93);
    printf("\n");
    
    bool dynamic_passed = run_test_suite("fibonacci_dynamic", fibonacci_dynamic, test_cases, num_tests, 93);
    
    printf("\nAll tests %s\n", 
           (recursive_passed && iterative_passed && dynamic_passed) ? "PASSED" : "FAILED");
    
    return (recursive_passed && iterative_passed && dynamic_passed) ? 0 : 1;
} 