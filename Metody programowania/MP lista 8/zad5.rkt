#lang plait

(define-type UnaryOp
  (op-neg) (op-fact))

(define-type BinaryOp
  (op-add) (op-mul) (op-sub) (op-pow) (op-div))

(define-type Exp
  (exp-number [n : Number])
  (exp-unary-op [op : UnaryOp] [e : Exp])
  (exp-binary-op [op : BinaryOp] [e1 : Exp] [e2 : Exp]))

(define (parse-UnaryOp s)
  (let ([sym (s-exp->symbol s)])
    (cond
      [(equal? sym '!) (op-fact)]
      [(equal? sym '~) (op-neg)])))

(define (parse-BinaryOp s)
  (let ([sym (s-exp->symbol s)])
    (cond
      [(equal? sym '+) (op-add)]
      [(equal? sym '-) (op-sub)]
      [(equal? sym '*) (op-mul)]
      [(equal? sym '/) (op-div)]
      [(equal? sym '^) (op-pow)])))


(define (expt-helper x y acc)
  (if (= y 0)
      acc
      (expt-helper x (- y 1) (* acc x))))

(define (^ x y)
  (if (> y 0)
      (expt-helper x y 1)
      (expt-helper (/ 1 x) (- 0 y) 1)))

(define (~ x)
  (* -1 x))

(define (! x)
  (if (= 0 x)
      1
      (* x (! (- x 1)))))

(define (eval-unary-op op)
  (type-case UnaryOp op
    [(op-fact) !]
    [(op-neg) ~]))

(define (eval-binary-op op)
  (type-case BinaryOp op
    [(op-add) +]
    [(op-sub) -]
    [(op-mul) *]
    [(op-div) /]
    [(op-pow) ^]))

(define (eval e)
  (type-case Exp e
    [(exp-number n)    n]
    ;operatory unarne
    [(exp-unary-op op e) ((eval-unary-op op) (eval e))]
    ;operatory binarne
    [(exp-binary-op op e1 e2)
     ((eval-binary-op op) (eval e1) (eval e2))]))


(define (parse-Exp s)
  (cond
    [(s-exp-number? s) (exp-number (s-exp->number s))]
    [(s-exp-list? s)
     (let ([xs (s-exp->list s)])
       ;rozważenie operatora binarnego i unarnego
       (if (= 2 (length xs))
           ;operator unarny
           (exp-unary-op (parse-UnaryOp (first xs))
                    (parse-Exp (second xs)))
           ;operator binarny
           (exp-binary-op (parse-BinaryOp (first xs))
               (parse-Exp (second xs))
               (parse-Exp (third xs)))))]))

(define (eval-Exp s)
  (eval (parse-Exp s)))

(parse-Exp `(^ 2 3))

(eval-Exp `(^ 2 3))
(eval-Exp `(^ 2 (! 3)))
(eval-Exp `(~ 3))