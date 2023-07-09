#lang racket

;sufiksy bez kontraktu
(define (suffixes xs)
  (if (null? xs)
      (cons xs null)
      (cons xs (suffixes(cdr xs)))))

;sufiksy z kontraktem
(define/contract (suffixes1 xs)
  (parametric->/c [a] (-> (listof a) (listof (listof a))))
  (if (null? xs)
      (cons xs null)
      (cons xs (suffixes1 (cdr xs)))))

(suffixes '(1 2 3 4))
(suffixes1 '(1 2 3 4))

(time (suffixes (range 3000)) (void))
(time (suffixes1 (range 3000)) (void))


