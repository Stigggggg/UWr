#lang plait

( define-type ( Formula 'v)
( var [ var : 'v ])
( neg [ f : ( Formula 'v) ])
( conj [ l : ( Formula 'v)] [r : ( Formula 'v) ])
( disj [ l : ( Formula 'v)] [r : ( Formula 'v) ]) )

(define (eval-formula sigma f)
  (cond [(var? f) (sigma (var-var f))]
        [(neg? f) (not (eval-formula sigma (neg-f f)))]
        [(conj? f) (and (eval-formula sigma (conj-l f)) (eval-formula sigma (conj-r f)))]
        [(disj? f) (or (eval-formula sigma (disj-l f)) (eval-formula sigma (disj-r f)))]))










