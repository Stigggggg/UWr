#lang racket

;pozytywne oznaczone \/

;(a b -> a)
;                              \/
;(parametric->/c [a b] (-> a b a))
(define/contract (f1 x y)
  (parametric->/c [a b] (-> a b a))
  x)

;((a b -> c) (a -> b) a -> c)
;                               \/ \/      \/      \/
;(parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
(define/contract (f2 f g x)
  (parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
  (f x (g x)))

;((b -> c) (a -> b) -> (a -> c))
;                               \/       \/          \/
;(parametric->/c [a b c] (-> (-> b c) (-> a b) (-> a c)))
(define/contract (f3 f g)
  (parametric->/c [a b c] (-> (-> b c) (-> a b) (-> a c)))
  (lambda (x) (f (g x))))

;(((a -> a) -> a) -> a)
;                                   \/    \/
;(parametric->/c [a] (-> (-> (-> a a) a) a))
(define/contract (f4 f)
  (parametric->/c [a] (-> (-> (-> a a) a) a))
  (f (lambda (x) (f (lambda (x) x)))))
  