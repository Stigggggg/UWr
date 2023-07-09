#lang racket

(define/contract (foldl-map f a xs)
  (parametric->/c [a acc c] (-> (-> a acc (cons/c c acc)) acc (listof a)
                              (cons/c (listof c) acc)))
  (define (it a xs ys)
    (if (null? xs)
        (cons (reverse ys) a)
        (let [(p (f (car xs) a))]
          (it (cdr p)
              (cdr xs)
              (cons (car p) ys)))))
  (it a xs null))

;procedura it przyjmuje 2 arg: a (akumulator), acc (lista dotychczasowych akumulatorów)
;następnie zwraca parę: nowy akumulator typu c (a dodane do acc) i acc - listę dotychczasowych akumulatorów