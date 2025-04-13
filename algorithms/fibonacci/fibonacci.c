#include <stdio.h>
#include <stdlib.h>

unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}


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