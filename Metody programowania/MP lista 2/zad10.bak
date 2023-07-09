#lang racket
(require rackunit)

(define (split xs)
  (define (it x xs)
    (if (= x 0)
        (list xs)
        (cons (car xs) (it (- x 1) (cdr xs)))))
  (reverse(it (quotient (length xs) 2) xs)))

(define (merge xs ys)
  (cond [(null? xs) ys]
        [(null? ys) xs]
        [else (if (< (car xs) (car ys))
                  (cons (car xs) (merge (cdr xs) ys))
                  (cons (car ys) (merge xs (cdr ys))))]))

(define (merge-sort xs)
  (if (= (length xs) 1)
      xs
      (let ([ys (split xs)])
      (merge (merge-sort (car ys)) (merge-sort (cdr ys))))))

(check equal? (split (list 8 2 4 7 4 2 1)) '((7 4 2 1) 4 2 8))
(check equal? (merge (list 1 4 4 8) (list 2 2 7)) '(1 2 2 4 4 7 8))
(check equal? (merge-sort (list 8 2 4 7 4 2 1)) '(1 2 2 4 4 7 8))
(check equal? (merge-sort (list 1 5 0 7 1 4 1 0)) '(0 0 1 1 1 4 5 7))