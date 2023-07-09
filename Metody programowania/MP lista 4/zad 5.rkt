#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define t
  (node
   (node (leaf) 2 (leaf))
   5
   (node (node (leaf) 6 (leaf))
         8
         (node (leaf) 9 (leaf)))))

(define (insert-bst-d x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond [(< x (node-elem t))
                 (node (insert-bst-d x (node-l t))
                       (node-elem t)
                       (node-r t))]
                [else
                 (node (node-l t)
                       (node-elem t)
                       (insert-bst-d x (node-r t)))])]))


(insert-bst-d 6 t)

(define (fold-tree f x t)
  (if (leaf? t)
      x
      (f (node-elem t) (fold-tree f x (node-l t)) (fold-tree f x (node-r t)))))

(define (flatten t)
  (fold-tree (lambda (elem l r) (append l (cons elem r))) '() t))

(define (treesort xs)
  (define (pom xs t)
    (if (empty? xs) (flatten t)
        (pom (cdr xs) (insert-bst-d (car xs) t))))
  (pom xs (leaf)))

(node (node (node (leaf) 1 (node (leaf) 2 (leaf))) 3 (node (leaf) 4 (leaf))) 5 (leaf))

(treesort (list 5 3 4 1 2))
  
