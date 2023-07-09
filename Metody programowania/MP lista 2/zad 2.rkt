#lang racket

; wersja rekurencyjna

(define (fib-r n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib-r (- n 1)) (fib-r (- n 2))))))

; wersja iteracyjna

(define (fib-i n)
  (define (it n a b)
    (if (= n 0)
        b
        (it (- n 1) (+ a b) a)))
  (it n 1 0))


;(fib-i 5)
;(it 5 1 0) -> (it 4 1 1) -> (it 3 2 1) -> (it 2 3 2) -> (it 1 5 3) -> (it 0 8 5) -> 5
   
          
    