#lang racket

(define (minimum xs)
  (cond ((null? xs) -inf.0)
        ((null? (cdr xs)) (car xs))
        (else (if (< (car xs) (minimum (cdr xs))) (car xs) (minimum (cdr xs))))))

(define (remove x xs)
   (if (null? xs)
      xs
      (if (= x (car xs))
      (remove x (cdr xs))
      (cons (car xs) (remove x (cdr xs))))))

(define (select xs)
   (define min (minimum xs))
   (cons min (remove min xs)))

(define (selection-sort xs)
   (if (null? xs)
      xs
      (cons (car (select xs)) (selection-sort (cdr (select xs))))))

