#lang plait 

(define-type (Tree 'a)
  (leaf)
  (node [l : (Tree 'a)] [elem : 'a] [r : (Tree 'a)]))

(define (process-tree comb leaf-comb l-acc r-acc acc t)
  (local [(define (process-tree-rec t acc)
            (if (leaf? t)
                (leaf-comb acc)
                (comb acc
                      (process-tree-rec (node-l t)
                                         (l-acc acc (node-elem t)))
                      (node-elem t)
                      (process-tree-rec (node-r t)
                                        (r-acc acc (node-elem t))))))]
    (process-tree-rec t acc)))

(define (bst? t)
  (process-tree
   (lambda (acc l-res el r-res) ; procedura kombinująca
     (and (< (fst acc) el)
          (< el (snd acc))
          l-res
          r-res))
   (lambda (x) #t) ; liść jest pustym drzewem, więc bst
   (lambda (acc el) (pair (fst acc) (min el (snd acc)))) ; akumulacja po lewej gałęzi
   (lambda (acc el) (pair (max el (fst acc)) (snd acc))) ; akumulacja po prawej gałęzi
   (pair -inf.0 +inf.0) ; w akumulatorze trzymamy przedział, gdzie mają być elementy
   t))

(define (sum-paths t)
  (process-tree
   (lambda (acc l-res el r-res)
     (node l-res
           (+ acc el)
           r-res))
   (lambda (x) (leaf)) ; liść jest takim drzewem jaki chcemy
   (lambda (acc el) (+ acc el)) ; akumulacja po lewej gałęzi
   (lambda (acc el) (+ acc el)) ; akumulacja po prawej gałęzi
   0
   t))