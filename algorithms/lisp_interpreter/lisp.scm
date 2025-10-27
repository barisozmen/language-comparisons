#!/usr/bin/env scheme
;;; A minimal Lisp interpreter in Scheme (meta-circular evaluator)
;;; Inspired by Peter Norvig's legendary implementation
;;; This is the most elegant form - Lisp implementing Lisp!

;; Environment operations
(define (make-env bindings outer-env)
  (cons bindings outer-env))

(define empty-env '())

(define (lookup var env)
  (if (null? env)
      (error "Unbound variable" var)
      (let ((binding (assoc var (car env))))
        (if binding
            (cdr binding)
            (lookup var (cdr env))))))

(define (extend-env vars vals env)
  (make-env (map cons vars vals) env))

(define (define! var val env)
  (set-car! env (cons (cons var val) (car env))))

;; Standard environment
(define (standard-env)
  (make-env
   `((+ . ,+)
     (- . ,-)
     (* . ,*)
     (/ . ,/)
     (< . ,<)
     (> . ,>)
     (= . ,=)
     (<= . ,<=)
     (>= . ,>=)
     (eq? . ,eq?)
     (equal? . ,equal?)
     (cons . ,cons)
     (car . ,car)
     (cdr . ,cdr)
     (list . ,list)
     (null? . ,null?)
     (pair? . ,pair?)
     (number? . ,number?)
     (symbol? . ,symbol?)
     (procedure? . ,procedure?)
     (not . ,not)
     (abs . ,abs)
     (max . ,max)
     (min . ,min)
     (length . ,length)
     (append . ,append)
     (map . ,map)
     (apply . ,apply)
     (display . ,display)
     (newline . ,newline)
     (#t . #t)
     (#f . #f))
   empty-env))

;; The heart of the interpreter: eval
(define (lisp-eval exp env)
  (cond
    ;; Self-evaluating expressions
    ((number? exp) exp)
    ((string? exp) exp)
    ((boolean? exp) exp)
    
    ;; Variables
    ((symbol? exp)
     (lookup exp env))
    
    ;; Special forms
    ((pair? exp)
     (case (car exp)
       ((quote)
        (cadr exp))
       
       ((if)
        (if (lisp-eval (cadr exp) env)
            (lisp-eval (caddr exp) env)
            (lisp-eval (cadddr exp) env)))
       
       ((define)
        (let ((var (cadr exp))
              (val (lisp-eval (caddr exp) env)))
          (define! var val env)
          var))
       
       ((lambda)
        (let ((params (cadr exp))
              (body (caddr exp)))
          (lambda args
            (lisp-eval body (extend-env params args env)))))
       
       ((begin)
        (let loop ((exps (cdr exp)))
          (if (null? (cdr exps))
              (lisp-eval (car exps) env)
              (begin
                (lisp-eval (car exps) env)
                (loop (cdr exps))))))
       
       ((set!)
        (let ((var (cadr exp))
              (val (lisp-eval (caddr exp) env)))
          (set-cdr! (assoc var (car env)) val)
          var))
       
       ;; Procedure application
       (else
        (let ((proc (lisp-eval (car exp) env))
              (args (map (lambda (arg) (lisp-eval arg env))
                        (cdr exp))))
          (apply proc args)))))
    
    (else
     (error "Unknown expression type" exp))))

;; Read-Eval-Print Loop
(define (lisp-repl)
  (let ((global-env (standard-env)))
    (display "Welcome to the Lisp interpreter written in Scheme!\n")
    (display "A meta-circular evaluator - Lisp implementing Lisp.\n")
    (let loop ()
      (display "lisp> ")
      (let ((input (read)))
        (if (eof-object? input)
            (begin
              (display "\nBye!\n")
              (newline))
            (begin
              (let ((result (lisp-eval input global-env)))
                (if (not (eq? result (if #f #f)))  ; Check for unspecified value
                    (begin
                      (write result)
                      (newline))))
              (loop)))))))

;; Alternative: evaluate a single expression
(define (lisp-eval-string str)
  (let ((exp (read (open-input-string str)))
        (env (standard-env)))
    (lisp-eval exp env)))

;; Example usage
(define (test-interpreter)
  (let ((env (standard-env)))
    (display "Testing the Lisp interpreter:\n\n")
    
    ;; Test 1: Arithmetic
    (display "Test: (+ 1 2 3)\n")
    (display "Result: ")
    (write (lisp-eval '(+ 1 2 3) env))
    (newline)
    (newline)
    
    ;; Test 2: Define variable
    (display "Test: (define x 10)\n")
    (lisp-eval '(define x 10) env)
    (display "Test: (* x 2)\n")
    (display "Result: ")
    (write (lisp-eval '(* x 2) env))
    (newline)
    (newline)
    
    ;; Test 3: Lambda
    (display "Test: ((lambda (x) (* x x)) 5)\n")
    (display "Result: ")
    (write (lisp-eval '((lambda (x) (* x x)) 5) env))
    (newline)
    (newline)
    
    ;; Test 4: Factorial using recursion
    (display "Test: Factorial function\n")
    (lisp-eval '(define fact 
                  (lambda (n)
                    (if (< n 2)
                        1
                        (* n (fact (- n 1)))))) env)
    (display "(fact 5) = ")
    (write (lisp-eval '(fact 5) env))
    (newline)
    (newline)))

;; Run REPL if this is the main module
;; (lisp-repl)

;; Or run tests
;; (test-interpreter)
