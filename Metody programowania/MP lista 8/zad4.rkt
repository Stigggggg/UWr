#lang plait

(define-type Op
  (op-add) (op-mul) (op-sub) (op-div))

(define (parse-Op s)
  (let ([sym (s-exp->symbol s)])
  (cond
    [(equal? sym '+) (op-add)]
    [(equal? sym '-) (op-sub)]
    [(equal? sym '*) (op-mul)]
    [(equal? sym '/) (op-div)])))

;trzeba polaczyc parse-exp i eval w jedno

(define (eval-exp s)
  (cond
    ;jak s-wyrażenie jest liczba, konwertujemy s na liczbe
    [(s-exp-number? s) (s-exp->number s)]
    ;jak jest lista to obliczam wartość
    [(s-exp-list? s)
     (let* ([xs (s-exp->list s)]
       ;parsuje do odpowiedniego symbolu
       [op (parse-Op (first xs))])
       (type-case Op op
         ;badam jaki mam dostępny symbol i rekurencyjnie obliczam wartości
           [(op-add) (+ (eval-exp (second xs)) (eval-exp (third xs)))]
           [(op-sub) (- (eval-exp (second xs)) (eval-exp (third xs)))]
           [(op-mul) (* (eval-exp (second xs)) (eval-exp (third xs)))]
           [(op-div) (/ (eval-exp (second xs)) (eval-exp (third xs)))]))]))

(eval-exp `(+ 2 (* 3 4)))
