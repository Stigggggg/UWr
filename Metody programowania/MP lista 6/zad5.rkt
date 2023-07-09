#lang plait

(define-type (NNF 'v)
  (nnf-lit [polarity : Boolean] [var : 'v])
  (nnf-conj [l : (NNF 'v)] [r : (NNF 'v)])
  (nnf-disj [l : (NNF 'v)] [r : (NNF 'v)]))

(define (eval-nnf sigma fi)
  (cond [(nnf-lit? fi) (if (nnf-lit-polarity fi) (sigma (nnf-lit-var fi)) (not (sigma (nnf-lit-var fi))))]
        [(nnf-conj? fi) (and (eval-nnf sigma (nnf-conj-l fi)) (eval-nnf sigma (nnf-conj-r fi)))]
        [(nnf-disj? fi) (or (eval-nnf sigma (nnf-disj-l fi)) (eval-nnf sigma (nnf-disj-r fi)))]))

(define test (nnf-conj (nnf-lit #t "p") (nnf-lit #f "q")))

(define (wart)
  (lambda (x) (cond [(equal? x "p") #t]
                    [(equal? x "q") #f])))

(eval-nnf (wart) test)




