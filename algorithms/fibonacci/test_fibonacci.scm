;;; Tests for Fibonacci algorithm implementations in Scheme.

;;; Load the implementations
(load "fibonacci.scm")

;;; Define test cases
(define test-cases
  '((0 . 0)
    (1 . 1)
    (2 . 1)
    (3 . 2)
    (4 . 3)
    (5 . 5)
    (10 . 55)
    (20 . 6765)))

;;; Test function that checks if the implementation gives the correct result
(define (test-function name func test-cases max-n)
  (display "Testing ")
  (display name)
  (display ":\n")
  
  (let ((all-passed #t))
    (for-each
     (lambda (test-case)
       (let ((input (car test-case))
             (expected (cdr test-case)))
         
         ;; Skip test cases that are too large
         (if (<= input max-n)
             (let ((result (func input)))
               (display "  ")
               (display name)
               (display "(")
               (display input)
               (display ") = ")
               (display result)
               (display ", expected: ")
               (display expected)
               (display " - ")
               
               (if (= result expected)
                   (display "PASS")
                   (begin
                     (display "FAIL")
                     (set! all-passed #f)))
               
               (newline))
             (begin
               (display "  Skipping test case ")
               (display input)
               (display " (too large for this implementation)\n")))))
     test-cases)
    
    all-passed))

;;; Run the tests
(define recursive-passed
  (test-function "fibonacci-recursive" fibonacci-recursive test-cases 20))
(newline)

(define iterative-passed
  (test-function "fibonacci-iterative" fibonacci-iterative test-cases 100))
(newline)

(define memoized-passed
  (test-function "fibonacci-memoized" fibonacci-memoized test-cases 100))
(newline)

;;; Print overall result
(display "All tests ")
(if (and recursive-passed iterative-passed memoized-passed)
    (display "PASSED")
    (display "FAILED"))
(newline)

;;; Exit with appropriate status code
(exit (if (and recursive-passed iterative-passed memoized-passed) 0 1)) 