;;; Define filter function if not available in the implementation
(define (filter pred lst)
  (cond ((null? lst) '())
        ((pred (car lst))
         (cons (car lst) (filter pred (cdr lst))))
        (else (filter pred (cdr lst)))))


;;; Fibonacci implementations in Scheme.
;;;
;;; This file contains both recursive and iterative implementations of the
;;; Fibonacci sequence calculation.

;;; Calculate the nth Fibonacci number recursively.
;;;
;;; Parameters:
;;;   n - A non-negative integer
;;;
;;; Returns:
;;;   The nth number in the Fibonacci sequence
;;;
;;; Note:
;;;   This implementation is simple but inefficient for large values of n
;;;   due to redundant calculations. Time complexity is O(2^n).
(define (fibonacci-recursive n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fibonacci-recursive (- n 1))
                 (fibonacci-recursive (- n 2))))))

;;; Calculate the nth Fibonacci number iteratively.
;;;
;;; Parameters:
;;;   n - A non-negative integer
;;;
;;; Returns:
;;;   The nth number in the Fibonacci sequence
;;;
;;; Note:
;;;   This implementation is more efficient with O(n) time complexity
;;;   and O(1) space complexity.
(define (fibonacci-iterative n)
  (if (< n 2)
      n
      (let loop ((a 0) (b 1) (count 2))
        (if (> count n)
            b
            (loop b (+ a b) (+ count 1))))))

;;; Calculate the nth Fibonacci number using memoization.
;;;
;;; Parameters:
;;;   n - A non-negative integer
;;;
;;; Returns:
;;;   The nth number in the Fibonacci sequence
;;;
;;; Note:
;;;   This implementation combines recursion with memoization for
;;;   improved performance. Time complexity is O(n).
(define fibonacci-memoized
  (let ((memo '()))
    (lambda (n)
      (let ((result (assoc n memo)))
        (if result
            (cdr result)
            (let ((value
                   (cond ((= n 0) 0)
                         ((= n 1) 1)
                         (else (+ (fibonacci-memoized (- n 1))
                                  (fibonacci-memoized (- n 2)))))))
              (set! memo (cons (cons n value) memo))
              value))))))

;;; A simple test function to verify results
(define (test-fibonacci)
  (define test-cases '(0 1 2 3 5 10 20))
  
  (display "Testing recursive implementation:\n")
  (for-each (lambda (n)
              (display "fibonacci-recursive(")
              (display n)
              (display ") = ")
              (display (fibonacci-recursive n))
              (newline))
            (filter (lambda (x) (<= x 20)) test-cases))
  
  (display "\nTesting iterative implementation:\n")
  (for-each (lambda (n)
              (display "fibonacci-iterative(")
              (display n)
              (display ") = ")
              (display (fibonacci-iterative n))
              (newline))
            test-cases)
  
  (display "\nTesting memoized implementation:\n")
  (for-each (lambda (n)
              (display "fibonacci-memoized(")
              (display n)
              (display ") = ")
              (display (fibonacci-memoized n))
              (newline))
            test-cases))

;;; Run the tests when this file is executed directly
(test-fibonacci) 