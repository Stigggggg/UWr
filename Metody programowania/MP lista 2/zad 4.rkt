#lang racket

(define-struct matrix (a b c d))

(define (matrix-mult m n)
  (make-matrix (+ (* (matrix-a m) (matrix-a n)) (* (matrix-b m) (matrix-c n)))
               (+ (* (matrix-a m) (matrix-b n)) (* (matrix-d m) (matrix-c n)))
               (+ (* (matrix-c m) (matrix-a n)) (* (matrix-d m) (matrix-c n)))
               (+ (* (matrix-c m) (matrix-b n)) (* (matrix-d m) (matrix-d n)))))

(define matrix-id (make-matrix 1 0 0 1))

; szybkie potegowanie macierzy
(define (matrix-expt-fast m k)
  (cond ((= k 0) matrix-id)
        ((= k 1) m)
        ([even? k] (matrix-expt-fast (matrix-mult m m) (/ k 2)))
        [else (matrix-mult m (matrix-expt-fast m (- k 1)))]))

; szybki fibonacci
(define (fib-fast k)
  (define m (make-matrix 1 1 1 0))
  (define n (matrix-expt-fast m k))
  (matrix-b n))
