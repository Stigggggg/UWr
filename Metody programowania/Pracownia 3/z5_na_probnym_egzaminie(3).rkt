#lang racket

(define-struct node (elem [next #:mutable] [next-next #:mutable]) #:transparent)

(define (insert-after-next node elem)
  (if (not (eq? (node-next node) (node-next-next node)))
      (let* ((next-next (node-next-next node))
             (next-next-next (node-next-next (node-next node))))
        (define new-node (make-node elem next-next next-next-next))
        (begin
          (set-node-next-next! node new-node)
          (set-node-next! (node-next node) new-node)
          (set-node-next-next! (node-next node) next-next)))
      (let [(new-node (make-node elem null null))]
        (begin
          (set-node-next! node new-node)
          (set-node-next! new-node node)
          (set-node-next-next! new-node new-node)))))
      
(define node1 (make-node 1 '() '()))
(set-node-next! node1 node1)
(set-node-next-next! node1 node1)
(insert-after-next node1 2)

