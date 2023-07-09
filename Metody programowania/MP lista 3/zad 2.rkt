#lang racket

(define (my-foldl f x xs)
  (define (it xs acc)
    (if (null? xs)
        acc
        (it (cdr xs) (f (car xs) acc))))
  (it xs x))

(define (my-sum xs)
  (my-foldl + 0 xs))

(define (product xs)
  (if (empty? xs)
      0
      (foldl * 1 xs)))

(product '(1 2 3 4))

