#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define (fold-tree f x t)
  (if (leaf? t)
      x
      (f (node-elem t) (fold-tree f x (node-l t)) (fold-tree f x (node-r t)))))

(define t
  (node
   (node (leaf) 2 (leaf))
   5
   (node (node (leaf) 6 (leaf))
         8
         (node (leaf) 9 (leaf)))))

(define (flatten t)
  (fold-tree (lambda (elem l r) (append l (cons elem r))) '() t))

(define (flatten-tree tree)
  (define (flat-append t xs)
    (if (leaf? t)
        xs
        (flat-append (node-l t)
                     (cons (node-elem t)
                           (flat-append (node-r t) xs)))))
  (flat-append tree '()))
  
(flatten-tree t)

