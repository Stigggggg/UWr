#lang racket

(define (my-foldr f x xs)
  (if (null? xs)
      x
      (f (car xs) (my-foldr f x (cdr xs)))))

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define t
  (node
   (node (leaf) 2 (leaf))
   5
   (node (node (leaf) 6 (leaf))
         8
         (node (leaf) 9 (leaf)))))

(define (fold-tree f x t)
  (if (leaf? t)
      x
      (f (node-elem t) (fold-tree f x (node-l t)) (fold-tree f x (node-r t)))))

(define (tree-sum t)
  (fold-tree + 0 t))

(define (tree-flip t)
  (fold-tree (lambda (elem l r) (node r elem l)) (leaf) t))

(define (tree-height t)
  (fold-tree (lambda (elem l r) (+ 1 (max l r))) 0 t))
 
(define (tree-span t)
  (cons (fold-tree (lambda (elem l r) (if (leaf? r) elem r)) (leaf) t)
        (fold-tree (lambda (elem l r) (if (leaf? l) elem l)) (leaf) t)))
      
(tree-span t)

(define (flatten t)
  (fold-tree (lambda (elem l r) (append l (cons elem r))) '() t))
        
(flatten t) 







  










      
      