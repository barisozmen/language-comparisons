;; Breadth-First Search: Level-by-level exploration

(define (bfs-iterative graph start goal)
  "Standard BFS with queue - finds shortest path"
  (if (equal? start goal)
      (list start)
      (let loop ((queue (list (list start (list start))))
                 (visited (list start)))
        (if (null? queue)
            '()
            (let* ((current (car queue))
                   (node (car current))
                   (path (cadr current))
                   (neighbors (cdr (assoc node graph))))
              (if (not neighbors)
                  (loop (cdr queue) visited)
                  (let check-neighbors ((nbrs neighbors)
                                        (new-queue (cdr queue))
                                        (new-visited visited))
                    (if (null? nbrs)
                        (loop new-queue new-visited)
                        (let ((neighbor (car nbrs)))
                          (cond
                            ((member neighbor new-visited)
                             (check-neighbors (cdr nbrs) new-queue new-visited))
                            ((equal? neighbor goal)
                             (append path (list neighbor)))
                            (else
                             (check-neighbors 
                               (cdr nbrs)
                               (append new-queue (list (list neighbor (append path (list neighbor)))))
                               (cons neighbor new-visited)))))))))))))


(define (bfs-level-order graph start)
  "BFS that returns nodes level by level"
  (let loop ((queue (list start))
             (visited (list start))
             (levels '()))
    (if (null? queue)
        (reverse levels)
        (let* ((level-size (length queue))
               (result (process-level graph queue visited level-size)))
          (loop (caddr result)           ; new queue
                (cadr result)            ; new visited
                (cons (car result) levels)))))) ; add level

(define (process-level graph queue visited count)
  "Process one level of BFS"
  (if (= count 0)
      (list '() visited queue)
      (let* ((node (car queue))
             (rest-queue (cdr queue))
             (neighbors (cdr (assoc node graph))))
        (if (not neighbors)
            (let ((result (process-level graph rest-queue visited (- count 1))))
              (list (cons node (car result)) (cadr result) (caddr result)))
            (let add-neighbors ((nbrs neighbors)
                                (v visited)
                                (q rest-queue))
              (if (null? nbrs)
                  (let ((result (process-level graph q v (- count 1))))
                    (list (cons node (car result)) (cadr result) (caddr result)))
                  (let ((neighbor (car nbrs)))
                    (if (member neighbor v)
                        (add-neighbors (cdr nbrs) v q)
                        (add-neighbors (cdr nbrs)
                                       (cons neighbor v)
                                       (append q (list neighbor)))))))))))

