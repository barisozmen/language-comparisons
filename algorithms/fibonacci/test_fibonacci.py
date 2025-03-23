"""
Tests for Fibonacci algorithm implementations in Python.
"""
import unittest
from fibonacci import fibonacci_recursive, fibonacci_iterative, fibonacci_optimized

class TestFibonacci(unittest.TestCase):
    def test_fibonacci_recursive(self):
        test_cases = {
            0: 0,
            1: 1,
            2: 1, 
            3: 2,
            4: 3,
            5: 5,
            10: 55,
            15: 610
        }
        
        for n, expected in test_cases.items():
            with self.subTest(n=n):
                self.assertEqual(fibonacci_recursive(n), expected)
    
    def test_fibonacci_iterative(self):
        test_cases = {
            0: 0,
            1: 1,
            2: 1, 
            3: 2,
            4: 3,
            5: 5,
            10: 55,
            20: 6765,
            30: 832040
        }
        
        for n, expected in test_cases.items():
            with self.subTest(n=n):
                self.assertEqual(fibonacci_iterative(n), expected)
    
    def test_fibonacci_optimized(self):
        test_cases = {
            0: 0,
            1: 1,
            2: 1, 
            3: 2,
            4: 3,
            5: 5,
            10: 55,
            20: 6765,
            30: 832040
        }
        
        for n, expected in test_cases.items():
            with self.subTest(n=n):
                self.assertEqual(fibonacci_optimized(n), expected)

if __name__ == '__main__':
    unittest.main() 