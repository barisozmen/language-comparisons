;; Conway's Game of Life - Scheme implementation

(define (neighbors cell)
  "Return list of 8 neighbors of a cell"
  (let ((x (car cell))
        (y (cadr cell)))
    (filter (lambda (c) (not (equal? c cell)))
            (apply append
                   (map (lambda (dx)
                          (map (lambda (dy) (list (+ x dx) (+ y dy)))
                               '(-1 0 1)))
                        '(-1 0 1))))))

(define (member-cell? cell cells)
  "Check if cell is in cells list"
  (if (null? cells)
      #f
      (if (equal? cell (car cells))
          #t
          (member-cell? cell (cdr cells)))))

(define (remove-duplicates lst)
  "Remove duplicate cells from list"
  (if (null? lst)
      '()
      (if (member-cell? (car lst) (cdr lst))
          (remove-duplicates (cdr lst))
          (cons (car lst) (remove-duplicates (cdr lst))))))

(define (neighbor-count cell cells)
  "Count live neighbors of a cell"
  (length (filter (lambda (n) (member-cell? n cells))
                  (neighbors cell))))

(define (candidates cells)
  "Get all cells that need to be checked"
  (remove-duplicates
   (append cells
           (apply append (map neighbors cells)))))

(define (step cells)
  "Compute next generation"
  (filter (lambda (cell)
            (let ((count (neighbor-count cell cells))
                  (alive (member-cell? cell cells)))
              (or (and alive (or (= count 2) (= count 3)))
                  (and (not alive) (= count 3)))))
          (candidates cells)))

(define (life cells generations)
  "Run Game of Life for given number of generations"
  (if (= generations 0)
      cells
      (life (step cells) (- generations 1))))

