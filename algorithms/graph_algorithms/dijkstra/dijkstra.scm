;; Dijkstra's Algorithm: Shortest path in weighted graphs

(define (dijkstra-heap graph start goal)
  "Dijkstra with priority queue simulation"
  (let loop ((pq (list (list 0 start (list start))))
             (visited '()))
    (if (null? pq)
        (list '() 999999)
        (let* ((pq-sorted (sort pq (lambda (a b) (< (car a) (car b)))))
               (current (car pq-sorted))
               (rest-pq (cdr pq-sorted))
               (cost (car current))
               (node (cadr current))
               (path (caddr current)))
          (cond
            ((member node visited)
             (loop rest-pq visited))
            ((equal? node goal)
             (list path cost))
            (else
             (let* ((new-visited (cons node visited))
                    (neighbors (cdr (assoc node graph)))
                    (new-items (if neighbors
                                   (filter (lambda (item) (not (member (cadr item) new-visited)))
                                           (map (lambda (edge)
                                                  (let ((neighbor (car edge))
                                                        (weight (cadr edge)))
                                                    (list (+ cost weight)
                                                          neighbor
                                                          (append path (list neighbor)))))
                                                neighbors))
                                   '())))
               (loop (append rest-pq new-items) new-visited))))))))


(define (dijkstra-all-paths graph start)
  "Dijkstra from single source to all nodes"
  (let* ((nodes (map car graph))
         (initial-dists (map (lambda (n) (list n 999999)) nodes)))
    (let loop ((pq (list (list 0 start)))
               (distances (update-distance initial-dists start 0))
               (visited '()))
      (if (null? pq)
          distances
          (let* ((pq-sorted (sort pq (lambda (a b) (< (car a) (car b)))))
                 (current (car pq-sorted))
                 (rest-pq (cdr pq-sorted))
                 (cost (car current))
                 (node (cadr current)))
            (if (member node visited)
                (loop rest-pq distances visited)
                (let* ((new-visited (cons node visited))
                       (neighbors (cdr (assoc node graph)))
                       (new-items (if neighbors
                                      (filter (lambda (item)
                                                (let ((neighbor (cadr item)))
                                                  (not (member neighbor new-visited))))
                                              (map (lambda (edge)
                                                     (let* ((neighbor (car edge))
                                                            (weight (cadr edge))
                                                            (new-dist (+ cost weight))
                                                            (curr-dist (cadr (assoc neighbor distances))))
                                                       (if (< new-dist curr-dist)
                                                           (list new-dist neighbor)
                                                           #f)))
                                                   neighbors))
                                      '()))
                       (valid-items (filter (lambda (x) x) new-items))
                       (updated-dists (fold-left (lambda (dists item)
                                                   (update-distance dists (cadr item) (car item)))
                                                 distances
                                                 valid-items)))
                  (loop (append rest-pq valid-items) updated-dists new-visited))))))))

(define (update-distance distances node new-dist)
  "Update distance for a node in association list"
  (map (lambda (entry)
         (if (equal? (car entry) node)
             (list node new-dist)
             entry))
       distances))

(define (fold-left f init lst)
  "Left fold implementation"
  (if (null? lst)
      init
      (fold-left f (f init (car lst)) (cdr lst))))

