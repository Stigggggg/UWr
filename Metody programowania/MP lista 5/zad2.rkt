#lang plait

(define (apply f x) (f x))
;(('a -> 'b) 'a -> 'b)
;bierze jako argumenty funkcje ('a -> 'b) i a, zwraca funkcje od a, czyli b
(define (compose f g) (lambda (x) (f (g x))))
;(('a -> 'b) ('c -> 'a) -> ('c -> 'b))
;bierze jako argumenty funkcje f: a->b i g: c->a
;g dziala na czyms i zwraca a, aplikuje do f wiec zwraca b
(define (flip f) (lambda (x y) (f y x)))
;(('a 'b -> 'c) -> ('b 'a -> 'c))
;bierze jako argument funkcje f: (a b -> c) i zwraca f z odwrocona kolejnoscia argumentow
(define (curry f) (lambda (x) (lambda (y) (f x y))))
;(('a 'b -> 'c) -> ('a -> ('b -> 'c)))
;bierze funkcje ktora przyjmuje 2 argumenty i zwraca nowa funkcje, ktora przyjmuje argument x i zwraca funkcje przyjmujaca y

;1)
;curry o typie (('a 'b -> 'c) -> ('a -> ('b -> 'c)))
;compose o typie (('a -> 'b) ('c -> 'a) -> ('c -> 'b))
;przepiszmy sobie typ compose używając innych nazw zmiennych typowych żeby się nie mieszało:
;compose - (('x -> 'y) ('z -> 'x) -> ('z -> 'y))
;i teraz (curry compose), jako pierwszy argument do curry o typie ('a 'b -> 'c) podstawiamy compose o typie (('x -> 'y) ('z -> 'x) -> ('z -> 'y)), czyli
;'a = ('x -> 'y)
;'b = ('z -> 'x)
;'c = ('z -> 'y)
;typ zwracany to ('a -> ('b -> 'c)), podstawiamy za 'a, 'b, i 'c odpowiednie typy:
;(('x -> 'y) -> (('z -> 'x) -> ('z -> 'y)))

;2)
;((curry compose) (curry compose))
;już wiemy, że (curry compose) ma typ (('_a -> '_b) -> (('_c -> '_a) -> ('_c -> '_b)))
;ponownie, przepiszmy sobie typ tego (curry compose) po prawej żeby się nie myliło:
;(('_x -> '_y) -> (('_z -> '_x) -> ('_z -> '_y)))
;i zaaplikujmy to:
;pierwszy argument do (curry compose) ma typ ('_a -> '_b), chcemy pod to podstawić (('_x -> '_y) -> (('_z -> '_x) -> ('_z -> '_y))), więc mamy:
;'_a = ('_x -> '_y)
;'_b = (('_z -> '_x) -> ('_z -> '_y))
;patrzymy na typ zwracany (('_c -> '_a) -> ('_c -> '_b)), podstawiamy zmienne:
;(('_c -> ('_x -> '_y)) -> ('_c -> (('_z -> '_x) -> ('_z -> '_y))))

;3)
; pomocnicze: (curry apply)
; a=(x->y)
; b=x
; c=y
; czyli (curry apply) zwroci typ: ('a -> ('b -> 'c)), czyli ((x->y)->(x->y))
; po podstawieniu tej funkcji jako argument do (curry compose)
; a=(x->y)
; b=(x->y)
;((curry compose) (curry apply)), co zwroci
;(('_a -> ('_b -> '_c)) -> ('_a -> ('b -> '_c)))

;4)
;curry apply - (('_a -> '_b) -> (('_c -> '_a) -> ('_c -> '_b)))
;curry curry compose -(('_a -> '_b) -> (('_c -> '_a) -> ('_c -> '_b)))
;czyli:
;a=(x->y)
;b=((z->x) -> (z->y))
;curry apply zwroci ('_a -> '_b)
;czyli ((x->y) -> ((z->x) -> (z->y)))
;po przelozeniu na aktualne typy:
;(('_a->'_b)->(('_c->'_a)->('_c->'_b)))

;5)
;compose - (('_a->'_b) ('_c->'_a) -> ('_c->'_b))
;zalozmy, ze f to curry i g to flip
;f:
;('a->'b) - ((x y -> z) -> (x -> (y -> z)))
;czyli a=(x y -> z) oraz b=(x->(y->z))
;g:
;('c -> 'a) = (('x 'y -> 'z) -> ('y 'x -> 'z))
;zatem:
;c=('x 'y -> 'z)
;a=('y 'x -> 'z)
;czyli x=y' i y=x' i z=z'
;compose zwraca ('c->'b)
;gdy podstawimy, mamy (('x 'y -> 'z) -> (x -> (y -> z))) -> ((y x -> z) (x -> (y -> z)))
;finalnie mamy: (('_a '_b -> '_c) -> ('_b -> ('_a -> '_c)))




