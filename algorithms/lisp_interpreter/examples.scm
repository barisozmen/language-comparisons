;;; Example Lisp/Scheme programs to run in any of the interpreters
;;; These examples showcase the core features implemented

;; Simple arithmetic
(+ 1 2 3)          ; => 6
(* 2 3 4)          ; => 24
(- 10 3)           ; => 7
(/ 20 4)           ; => 5

;; Comparisons
(< 3 5)            ; => true/1
(> 10 5)           ; => true/1

;; Variables
(define x 10)
(* x 2)            ; => 20

;; Lambda (anonymous functions)
((lambda (x) (* x x)) 5)                    ; => 25
((lambda (x y) (+ x y)) 3 4)               ; => 7

;; Higher-order functions
(define square (lambda (x) (* x x)))
(square 7)         ; => 49

(define twice (lambda (f x) (f (f x))))
(twice square 3)   ; => 81  (square of square of 3)

;; Recursion: Factorial
(define fact
  (lambda (n)
    (if (< n 2)
        1
        (* n (fact (- n 1))))))
(fact 5)           ; => 120
(fact 10)          ; => 3628800

;; Recursion: Fibonacci
(define fib
  (lambda (n)
    (if (< n 2)
        n
        (+ (fib (- n 1))
           (fib (- n 2))))))
(fib 10)           ; => 55

;; List operations
(list 1 2 3)       ; => (1 2 3)
(car (list 1 2 3)) ; => 1
(cdr (list 1 2 3)) ; => (2 3)
(cons 0 (list 1 2 3)) ; => (0 1 2 3)

;; Conditional expressions
(define abs-val
  (lambda (x)
    (if (< x 0)
        (- x)
        x)))
(abs-val -5)       ; => 5
(abs-val 3)        ; => 3

;; Nested functions and closures
(define make-adder
  (lambda (n)
    (lambda (x) (+ x n))))
(define add5 (make-adder 5))
(add5 10)          ; => 15

;; More complex recursion: Sum of list
(define sum-list
  (lambda (lst)
    (if (null? lst)
        0
        (+ (car lst) (sum-list (cdr lst))))))
(sum-list (list 1 2 3 4 5)) ; => 15

;; Map (if supported)
;; (map square (list 1 2 3 4)) ; => (1 4 9 16)

