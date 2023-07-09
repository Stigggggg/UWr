#lang racket

;E -> E+M, E-M, M
;M -> M*P, M/P, P
;P -> F, F^P
;F -> N, -F, F!, (E)
;N -> D, DZN
;D -> 1,2,3,4,5,6,7,8,9
;Z -> 0, epsilon, ZZ