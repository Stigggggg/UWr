#lang racket

(define (mreverse! xs)
  (define (my-reverse prev curr)
    (if (null? curr)
        prev
        (let [(next (mcdr curr))]
          (set-mcdr! curr prev)
          (my-reverse curr next))))
  (my-reverse '() xs))

(define x (mcons 1 (mcons 2 (mcons 3 null))))
