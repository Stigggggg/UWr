#lang racket

(require (only-in plait s-exp-content))
(provide (contract-out [run-parser (-> (listof (list/c (listof any/c) procedure?)) s-exp-content any/c)]))
;run-parser bierze 2 arg: p, czyli listę definicji parserów i wyrażenie s do parsowania
;kontrakt list/c precyzuje, że każdy element listy p to lista wzorców dla parsera, a drugi to funkcja, która jest wywołana, gdy wyrażenie pasuje do wzorca

(define (match-sexp pat s)
  (match pat
    ['ANY    (list s)]
    ['SYMBOL (and (symbol? s) (list s))]
    ['NUMBER (and (number? s) (list s))]
    ['()     (and (null? s)   null)]
    [(cons p1 p2)
     (and (pair? s)
          (let ([r1 (match-sexp p1 (car s))])
            (and r1
                 (let ([r2 (match-sexp p2 (cdr s))])
                   (and r2 (append r1 r2))))))]
    [_
     (cond
       [(symbol? pat) (and (symbol? s) (eq? pat s) null)])]))

(define (run-parser p s)
  (match p
    ['() (error "Syntax error")]
    [(cons (list pat action) rest-p)
     (let ([r (match-sexp pat s)])
       (if r
           (apply action r)
           (run-parser rest-p s)))]))
