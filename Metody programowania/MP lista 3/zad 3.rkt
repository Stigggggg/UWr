#lang racket

;((lambda (x y) (+ x (* x y))) 1 2) -> (+ 1 (* 1 2)) -> 3

;((lambda (x) x) (lambda (x) x))
; -> ((lambda ((lambda (x) x))(lambda (x) x)) y)
; -> ((lambda (x) x) y) -> y

; (( lambda (x) (x x)) ( lambda (x) x))
; -> ((lambda ((lambda (x) x)) ((lambda (x) x) (lambda (x) x ))))
; -> ((lambda ((lambda (x) x)) ((lambda ((lambda (x) x)) (lambda (x) x )))))
; -> ((lambda ((lambda (x) x)) ((lambda (x) x))))
; -> ((lambda ((lambda (x) x)) x))
; -> ((lambda (x) x))
; -> x

;((lambda (x) (x x)) (lambda (x) (x x)) y)
; -> ((lambda ((lambda (x) (x x))) ((lambda (x) (x x)) (lambda (x) (x x))) x) itd, bedzie nieskonczona rekurencja
