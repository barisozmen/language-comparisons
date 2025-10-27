;; Depth-First Search: Explore deep before backtracking

(define (dfs-recursive graph start goal visited)
  "Classic recursive DFS - elegant but stack-limited"
  (cond
    ((equal? start goal) (list start))
    ((member start visited) '())
    (else
     (let ((new-visited (cons start visited))
           (neighbors (cdr (assoc start graph))))
       (if (not neighbors)
           '()
           (let loop ((nbrs neighbors))
             (if (null? nbrs)
                 '()
                 (let ((path (dfs-recursive graph (car nbrs) goal new-visited)))
                   (if (null? path)
                       (loop (cdr nbrs))
                       (cons start path))))))))))


(define (dfs-iterative graph start goal)
  "Iterative DFS using explicit stack"
  (let loop ((stack (list (list start (list start))))
             (visited '()))
    (if (null? stack)
        '()
        (let* ((current (car stack))
               (node (car current))
               (path (cadr current)))
          (cond
            ((member node visited)
             (loop (cdr stack) visited))
            ((equal? node goal)
             path)
            (else
             (let* ((new-visited (cons node visited))
                    (neighbors (cdr (assoc node graph)))
                    (new-items (if neighbors
                                   (map (lambda (n)
                                          (list n (append path (list n))))
                                        (reverse neighbors))
                                   '())))
               (loop (append new-items (cdr stack)) new-visited))))))))


(define (dfs-postorder graph start visited)
  "DFS that returns nodes in postorder"
  (if (member start visited)
      (list visited '())
      (let* ((new-visited (cons start visited))
             (neighbors (cdr (assoc start graph))))
        (if (not neighbors)
            (list new-visited (list start))
            (let loop ((nbrs neighbors)
                       (v new-visited)
                       (result '()))
              (if (null? nbrs)
                  (list v (append result (list start)))
                  (let* ((sub-result (dfs-postorder graph (car nbrs) v))
                         (updated-visited (car sub-result))
                         (sub-nodes (cadr sub-result)))
                    (loop (cdr nbrs) updated-visited (append result sub-nodes)))))))))

