#lang racket

(define (cycle! xs)
  (define (last xs)
    (if (empty? xs)
        (error "Lista jest pusta")
        (if (null? (mcdr xs))
            xs
            (last (mcdr xs)))))
  (set-mcdr! (last xs) xs))

(define x (mcons 1 (mcons 2 (mcons 3 null))))
