#lang racket

; zad 5
(define (elem? x xs)
  (cond ((null? xs) #f)
        ((= x (car xs)) #t)
        (else (elem? x (cdr xs)))))

; zad 6
(define (maximum xs)
  (cond ((null? xs) -inf.0)
        ((null? (cdr xs)) (car xs))
        (else (if (> (car xs) (maximum (cdr xs))) (car xs) (maximum (cdr xs))))))

; zad 7
(define (suffixes xs)
  (if (null? xs)
      (cons xs null)
      (cons xs (suffixes(cdr xs)))))

; zad 8
(define (sorted? xs)
  (if (null? xs) #t
      (if (null? (cdr xs)) #t
                 (if (> (car xs) (cadr xs)) #f (sorted? (cdr xs))))))


     
  