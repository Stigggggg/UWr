#lang plait

;typ drzewa 2-3

(define-type (23trees 'v)
  (leaf [var1 : 'v])
  (2node [var1 : 'v] [l : (23trees 'v)] [r : (23trees 'v)])
  (3node [var1 : 'v] [var2 : 'v] [l : (23trees 'v)] [mid : (23trees 'v)] [r : (23trees 'v)]))

;sprawdzanie dlugosci wszystkich sciezek

(define (all tree)
  (cond
    [(leaf? tree) (list 0)]
    [(2node? tree)
     (append (map add1 (all (2node-l tree)))
             (map add1 (all (2node-r tree))))] 
    [(3node? tree)
     (append
      (append (map add1 (all (3node-l tree)))
             (map add1 (all (3node-mid tree))))
             (map add1 (all (3node-r tree))))]))

(define (helper p)
  (cond [(empty? (rest p)) #t]
        [(= (first p) (first (rest p))) (helper (rest p))]
        [else #f]))

(define (same? tree)
  (helper (all tree)))

(define (23tree? t min max)
  (cond [(leaf? t)
         (and (< min (leaf-var1 t)) (> max (leaf-var1 t)))]
        [(2node? t)
         (if (and (< min (2node-var1 t)) (> max (2node-var1 t)))
             (and (23tree? (2node-l t) min (2node-var1 t))
                  (23tree? (2node-r t) (2node-var1 t) max))
             #f)]
        [(3node? t)
         (if (and (< (3node-var1 t) (3node-var2 t))
                  (and
                   (and (< min (3node-var1 t)) (> max (3node-var1 t)))
                   (and (< min (3node-var2 t)) (> max (3node-var2 t)))))
             (and (23tree? (3node-l t) min (3node-var1 t))
                  (23tree? (3node-r t) (3node-var2 t) max)
                  (23tree? (3node-mid t) (3node-var1 t) (3node-var2 t)))
             #f)]))

(define (is23tree? t)
  (and (same? t) (23tree? t -inf.0 +inf.0)))

(define my23tree
  (2node 6 (3node 2 4 (leaf 1)(leaf 3)(leaf 5))
         (3node 9 11 (leaf 7)(leaf 10)(leaf 12))))

(all my23tree)
(same? my23tree)



