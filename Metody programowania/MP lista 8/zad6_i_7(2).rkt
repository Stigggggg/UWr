#lang plait

(define-type Exp
  (exp-var    [name : Symbol] [value : Exp])
  (exp-num [n : Number])
  (exp-lambda [args : (Listof Symbol)] [body : Exp])
  ;typ na zmienne lokalne funkcji
  (exp-loc-var [name : Symbol])
  (exp-app    [fn : Symbol] [args : (Listof Exp)])
  (exp-let    [variables : (Listof Exp)] [body : Exp])
  (exp-if     [clause : Exp] [if-true : Exp] [if-false : Exp])
  (exp-cond   [clauses : (Listof Exp)] [if-trues : (Listof Exp)]))

;pomocnicza funkcja - przyjmuje liste s-exp i zwraca liste symboli
(define (get-sym-list l)
  (map
    (lambda (x) (s-exp->symbol x))
    l))

(define (parse-Exp e)
  (cond[(s-exp-number? e) (exp-num (s-exp->number e))]
       [(s-exp-symbol? e) (exp-loc-var (s-exp->symbol e))]
       [(s-exp-list? e)
          (let ([xs (s-exp->list e)])
            (cond[(equal? (s-exp->symbol (first xs)) 'define)
                    (exp-var
                      (s-exp->symbol (second xs))
                      (parse-Exp (third xs)))]
                 [(equal? (s-exp->symbol (first xs)) 'lambda)
                    (exp-lambda
                      (get-sym-list (s-exp->list (second xs)))
                      (parse-Exp (third xs)))]
                 [(equal? (s-exp->symbol (first xs)) 'let)
                    (exp-let
                      ;z każdego s-exp w wejściowej liście robimy exp-var
                      (map
                          (lambda (x)
                            (exp-var 
                              (s-exp->symbol (first  (s-exp->list x))) 
                              (parse-Exp     (second (s-exp->list x)))))
                          (s-exp->list (second xs)))
                      (parse-Exp (third xs)))]
                 [(equal? (s-exp->symbol (first xs)) 'if)
                    (exp-if
                      (parse-Exp (second xs))
                      (parse-Exp (third xs))
                      (parse-Exp (fourth xs)))]
                 [(equal? (s-exp->symbol (first xs)) 'cond)
                    (exp-cond
                      (map
                        (lambda (x)(parse-Exp (first (s-exp->list x))))
                        (rest xs))
                      (map
                        (lambda (x)(parse-Exp (second (s-exp->list x))))
                        (rest xs)))]
                 [(s-exp-symbol? (first xs))
                    (exp-app
                      (s-exp->symbol (first xs))
                      ;parsujemy każdy z argumentów do funkcji 
                      (map
                        (lambda (x) (parse-Exp x))
                        (rest xs))
                    )]))]))




(define ex `(define x 5))
; ex
; (parse-Exp ex)
(define ex1 `(lambda (x y) (+ 5 (+ x y))))
; (parse-Exp ex1)
(define ex2 `(lambda (x) (f x (+ y 3))))
; (parse-Exp ex2)
(define ex3 `(* x (f x)))
; (parse-Exp ex3)
(define ex4 `(let ([x (+ 1 4)] [y 7]) (+ x y)))
; (parse-Exp ex4)
(define ex5 `(if (> x 5) y 1))
; (parse-Exp ex5)
(define ex6 `(cond [(> 3 x) x] [(= 3 x) (* -1 x)] [(< 3 x) (+ 42 x)]))
; (parse-Exp ex6)