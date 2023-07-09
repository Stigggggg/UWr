#lang plait

(define-type (NNF 'v)
  (nnf-lit [polarity : Boolean] [var : 'v])
  (nnf-conj [l : (NNF 'v)] [r : (NNF 'v)])
  (nnf-disj [l : (NNF 'v)] [r : (NNF 'v)]))

(define (neg-nnf fi)
  (cond [(nnf-lit? fi) (nnf-lit (not (nnf-lit-polarity fi)) (nnf-lit-var fi))]
        [(nnf-conj? fi) (nnf-disj (neg-nnf (nnf-conj-l fi)) (neg-nnf (nnf-conj-r fi)))]
        [(nnf-disj? fi) (nnf-conj (neg-nnf (nnf-disj-l fi)) (neg-nnf (nnf-disj-r fi)))]))

(define test (nnf-conj (nnf-lit #t "p") (nnf-lit #f "q")))