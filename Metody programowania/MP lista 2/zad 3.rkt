#lang racket

(define-struct matrix (a b c d))

;(define m (make-matrix 1 2 3 4))
;(matrix-b m)

; mnozenie macierzy
(define (matrix-mult m n)
  (make-matrix (+ (* (matrix-a m) (matrix-a n)) (* (matrix-b m) (matrix-c n)))
               (+ (* (matrix-a m) (matrix-b n)) (* (matrix-d m) (matrix-c n)))
               (+ (* (matrix-c m) (matrix-a n)) (* (matrix-d m) (matrix-c n)))
               (+ (* (matrix-c m) (matrix-b n)) (* (matrix-d m) (matrix-d n)))))

; macierz identycznosciowa
(define matrix-id (make-matrix 1 0 0 1))

; potegowanie macierzy
(define (matrix-expt m k)
  (cond ((= k 0) matrix-id)
        ((= k 1) m)
        (else (matrix-mult m (matrix-expt m (- k 1))))))

; k-ta liczba fibonacciego na macierzach
(define (fib-matrix k)
  (define m (make-matrix 1 1 1 0))
  (define n (matrix-expt m k))
  (matrix-b n))

;(matrix-a (matrix-mult (matrix 2 3 4 6) (matrix -1 5 7 2)))
;(matrix-b (matrix-mult (matrix 2 3 4 6) (matrix -1 5 7 2)))
;(matrix-c (matrix-mult (matrix 2 3 4 6) (matrix -1 5 7 2)))
;(matrix-d (matrix-mult (matrix 2 3 4 6) (matrix -1 5 7 2)))

