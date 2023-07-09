#lang racket

(define (fold-right f acc xs) ;bledna
  (if (null? xs)
      acc
      (f (car xs) (fold-right f (car xs) (cdr xs)))))

(define (my-foldr f x xs) ;poprawna
  (if (empty? xs)
      x
      (f (first xs) (my-foldr f x (rest xs)))))

;bledny kontrakt: (parametric->/c [a] (-> (-> a a a) a (listof a) a))
;poprawny kontrakt: (parametric->/c [a b] (-> (-> a b b) b (listof a) b))

;odp do 1: chcemy by byl typ a, a typ a maja argumenty listy xs stad musimy uzyc first xs

;odp do 2: Czy zmieniona wersja kontraktu ogranicza sposób użytkowania procedury? A zmieniona wersja typu?
;Tak, bo kontrprzykład: 

(my-foldr + 1 '(2 3 4 5))
(fold-right + 1 '(2 3 4 5))

;w fold-right przez to ze mamy first xs, to dodamy + 1 do kazdego elementu listy,
;natomiast w zwyklym foldrzer dodajemy 1 do sumy elementow listy. stad ogracza uzytkowanie procesu, zmieniona wersja typu tez (bo frist xs)