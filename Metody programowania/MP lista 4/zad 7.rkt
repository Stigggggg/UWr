#lang racket

;definicje z tresci zadania

(define empty-queue null)

(define (empty? q) 
  (null? q))

(define (push-back x q)
   (append q (list x)))

(define (front q) 
  (car q))

(define (pop q) 
  (cdr q))

;zmienione definicje

(define empty-queue-2 (cons (list) (list)))

(define (empty2? q)
  (null? (car q)))

(define (push-back2 x q)
  (if (empty2? q)
      (cons (list x) '())
      (cons (car q) (cons x (cdr q)))))

(define (front2 q)
  (car (car q)))

(define (pop2 q)
  (if (empty2? q)
      (empty-queue-2)
      (if (empty? (cdr (car q)))
          (cons (reverse (cdr q)) (list))
          (cons (cdr (car q)) (cdr q)))))

(pop2 (cons '(1 2 3) '(3 2 1)))


      
      


