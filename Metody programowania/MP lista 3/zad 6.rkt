#lang racket

(define empty-set (lambda (x) #f))

(define (singleton a)
  (lambda (x) (equal? a x)))

;((singleton 5) 5)

(define (in a s) ;s to procedura, która zwraca #t, gdy element należy do s, i #f, gdy nie należy
  (s a))

;(in 5 (singleton 3))

(define (union s t)
  (lambda (x) (or (s x) (t x))))

(define (intersect s t)
  (lambda (x) (and (s x) (t x))))

((union (singleton 5) (singleton 3)) 5)

((intersect (singleton 5) (singleton 5)) 5)











