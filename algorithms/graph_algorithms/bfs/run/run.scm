#!/usr/bin/env guile
!#

(load "../bfs.scm")

(define graph
  '((A B C)
    (B D E)
    (C F)
    (D)
    (E F)
    (F)))

(define tests
  '((A F)
    (A D)
    (A E)
    (B F)))

(for-each
  (lambda (test)
    (let ((start (car test))
          (goal (cadr test)))
      (display (format #f "BFS ~a->~a: ~a~%" start goal (bfs-iterative graph start goal)))))
  tests)

