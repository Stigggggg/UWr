#lang racket

;zad 8
(define (list->llist x)
  (lambda (y)(foldr cons y x)))

(define (llist->list f)
  (f '()))

(define llist-null
  (lambda(y) y))

(define (llist-singleton x) (list->llist (list x)))

(define (list-append f g)
  (lambda(x)(f(g x))))