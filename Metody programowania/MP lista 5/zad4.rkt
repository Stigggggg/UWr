#lang plait

(module+ test
  (print-only-errors #t))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (concat-map [f : ('a -> (Listof 'b))] [xs : (Listof 'a)]) : (Listof 'b)
  (if (empty? xs)
      empty
      (append (f (first xs))
              (concat-map f (rest xs)))))

(module+ test
  (test (concat-map (λ (x) (list (- x 1) (+ x 1))) '(1 2 3))
        '(0 2 1 3 2 4)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (insert-everywhere [a : 'a] [xs : (Listof 'a)]) : (Listof (Listof 'a))
  (if (empty? xs)
      (list (list a))
      (cons (cons a xs)
            (map (λ (ys) (cons (first xs) ys))
                 (insert-everywhere a (rest xs))))))

(module+ test
  (test (insert-everywhere 1 '(2 3 4))
        '((1 2 3 4) (2 1 3 4) (2 3 1 4) (2 3 4 1))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (perms [xs : (Listof 'a)]) : (Listof (Listof 'a))
  (if (empty? xs)
      (list empty)
      (concat-map (λ (ys) (insert-everywhere (first xs) ys))
                  (perms (rest xs)))))

(module+ test
  (test (perms '())
        '(()))
  (test (perms '(1))
        '((1)))
  (test (perms '(1 2 3))
        '((1 2 3) (2 1 3) (2 3 1) (1 3 2) (3 1 2) (3 2 1))))
