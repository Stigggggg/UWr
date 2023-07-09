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

(define (bst? t)
  (define (bst-helper node min-val max-val)
    (cond ((leaf? node) #t)
          ((and (< min-val (node-elem node))
                (> max-val (node-elem node)))
           (and (bst-helper (node-l node) min-val (node-elem node))
                (bst-helper (node-r node) (node-elem node) max-val)))
          (else #f)))
  (cond ((leaf? t) #t)
        ((node? t) (bst-helper t -inf.0 +inf.0))
        (else #f)))

;(bst? t)

(define (sum-paths t)
  (define (sum-paths-helper t sum-so-far)
    (cond
      [(leaf? t) (leaf)]
      [(node? t)
       (node (sum-paths-helper (node-l t) (+ sum-so-far (node-elem t)))
             (+ sum-so-far (node-elem t))
             (sum-paths-helper (node-r t) (+ sum-so-far (node-elem t))))]))
  (sum-paths-helper t 0))

(sum-paths t)

