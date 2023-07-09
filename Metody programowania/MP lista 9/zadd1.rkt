#lang racket


;E -> M | E+M | E-M
;M -> M*P | M / P | P
;P -> F | F^P
;F -> N | -N | N! | (E)
;N -> D | Z | DN
;D -> 1 2 3 4 5 6 7 8 9
;Z -> 0