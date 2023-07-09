#lang plait

;('a 'b -> 'a)
(define (f1 a b)
  a)
;(('a 'b -> 'c) ('a -> 'b) 'a -> 'c)
(define (f2 f g x)
  (f x (g x)))
;((('a -> 'a) -> 'a) -> 'a)
(define (i x) x)
(define (pom h ii) (ii (h ii)))
(define (f3 h) (pom h i))
;(define (f3 h) (i (h i)))
;(('a -> 'b) ('a -> 'c) -> ('a -> ('b *'c)))
(define (f4 f g)
  (lambda (x) (values (f x) (g x))))
;(('a -> (Optionof ('a * 'b))) 'a -> (Listof 'b))
(define (f5 f a)
  (if (none? (f a))
      '()
      (if (none? (f (fst (some-v (f a)))))
          (list (snd (some-v (f a))))
          (list (snd (some-v (f a)))))))
;alternatywne rozwiazanie
;(define (f5 f a)
;  (let ([res (f a)])
;        [(if (none? res)
;             '()
;             (cons (snd (some-v res)) (f5 f (fst (some-v res)))))]))
       
  





  


