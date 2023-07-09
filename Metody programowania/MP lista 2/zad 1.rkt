#lang racket

;(let ([x 3])
;  (+ x y))
; y wolny, x zwiazany

;(let ([x 1]
;      [y (+ x 2)])
;    (+ x y))
; x zwiazany z [x 1], ale nie z [y (+ x 2)]
; y zwiazany z [y (+ x 2)]

;(let ([x 1])
;  (let ([y (+ x 2)])
;    (* x y)))
; x zwiazany z [x 1] i z [y (+ x 2)]
; y zwiazany z [y (+ x 2)]

;(define (f x y)
;  (* x y z))
; zwiazane: f, x i y (linia 18), wiazace: f,x i y (linia 17), wolne: z

;(define (f x)
;  (define (g y z)
;    (* x y z))
;  (f x x x))
; zwiazane: x i y (linia 23), x (linia 24), wiazace: x (linia 21), y (linia 22)
