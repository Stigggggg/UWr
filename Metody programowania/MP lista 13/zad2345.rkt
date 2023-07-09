#lang racket

;; processing data sequences with lists --------------------

(define (second-prime-in-interval a b)
  (car (cdr (filter prime?
                    (enumerate-interval a b)))))

; (second-prime-in-interval 10000 5000000)

(define (enumerate-interval a b)
  (if (> a b)
      '()
      (cons a (enumerate-interval (+ a 1) b))))

(define (square x)
  (* x x))

(define (smallest-divisor n)
  (find-divisor n 2))

(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisor n (+ test-divisor 1)))))

(define (divides? a b)
  (= (remainder b a) 0))

(define (prime? n)
  (= n (smallest-divisor n)))

;; streams aka lazy lists ---------------------------------

;; delay and force

(define-syntax-rule
  (stream-cons v s)
  (cons v (delay s)))

(define stream-car car)

(define (stream-cdr s)
  (force (cdr s)))

(define stream-null null)
(define stream-null? null?)

;; operations on streams

(define (stream-ref s n)
  (if (= n 0)
      (stream-car s)
      (stream-ref (stream-cdr s) (- n 1))))

(define (stream-filter p s)
  (if (stream-null? s)
      stream-null
      (if (p (stream-car s))
          (stream-cons (stream-car s)
                       (stream-filter p (stream-cdr s)))
          (stream-filter p (stream-cdr s)))))

(define (stream-enumerate-interval a b)
  (if (> a b)
      stream-null
      (stream-cons a (stream-enumerate-interval (+ a 1) b))))

(define (stream-second-prime-in-interval a b)
  (stream-car
   (stream-cdr
    (stream-filter prime?
                   (stream-enumerate-interval a b)))))

;; infinite streams

(define ones (stream-cons 1 ones))

(define (integers-from n)
  (stream-cons n (integers-from (+ n 1))))

(define nats (integers-from 0))

(define (sieve s)
  (stream-cons
   (stream-car s)
   (sieve
    (stream-filter
     (λ (x) (not (divides? (stream-car s) x)))
     (stream-cdr s)))))

(define primes (sieve (integers-from 2)))

 ;; combining (infinite) streams 

(define (map2 f xs ys)
  (stream-cons
   (f (stream-car xs)
      (stream-car ys))
   (map2 f (stream-cdr xs) (stream-cdr ys))))

(define nats2 (stream-cons 0 (map2 + nats2 ones)))

#|
nats2    0 1 2 ...
ones     1 1 1 ...
---------------------------------------
nats2  0 1 2 3 ...
|#

(define fibs
  (stream-cons 0 (stream-cons 1 (map2 + fibs (stream-cdr fibs)))))

#|
fib            0 1 1 2 3 ...  
(cdr fib)      1 1 2 3 ...
-----------------------------------------
fib        0 1 1 2 3 5 ...

|#

;; our own implementation of delay and force (needs to be moved at the top of the file)

#|
(define (memo-proc proc)
  (let ([already-run? false]
        [result false])
    (lambda ()
      (if (not already-run?)
          (begin (set! result (proc))
                 (set! already-run? true)
                 result)
          result))))

(define-syntax-rule
  (delay c)
  (memo-proc (λ () c)))

(define (force t)
  (t))
|#

;zad 3
(define factorials
  (stream-cons 1 (map2 * (integers-from 1) factorials)))

(stream-car (stream-cdr factorials))
(stream-cdr (stream-cdr (stream-cdr factorials)))

;zad 4
(define (partial-sums s)
  (stream-cons (stream-car s) (map2 + (partial-sums s) (stream-cdr s))))

(define p (partial-sums (integers-from 0)))

(stream-car p)
(stream-cdr (stream-cdr p))

;zad 5
(define (merge s1 s2)
  (let ([s1-car (stream-car s1)]
        [s2-car (stream-car s2)])
    (cond [(= s1-car s2-car)
           (stream-cons s1-car (merge (stream-cdr s1) (stream-cdr s2)))]
          [(< s1-car s2-car)
           (stream-cons s1-car (merge (stream-cdr s1) s2))]
          [else (stream-cons s2-car (merge s1 (stream-cdr s2)))])))

(define (scale s n)
  (stream-cons (* n (stream-car s)) (scale (stream-cdr s) n)))

(define hamming
  (letrec ([s2 (stream-cons 2 (merge (scale s2 2) (merge (scale s2 3) (scale s2 5))))]
           [s3 (stream-cons 3 (merge (scale s3 2) (merge (scale s3 3) (scale s3 5))))]
           [s5 (stream-cons 5 (merge (scale s5 2) (merge (scale s5 3) (scale s5 5))))])
    (merge s2 (merge s3 s5))))
         