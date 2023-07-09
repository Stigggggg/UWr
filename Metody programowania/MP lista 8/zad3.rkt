#lang racket

(provide
 dequeue?
 empty-dequeue
 nonempty-dequeue/c
 (contract-out
  [dequeue-empty?     (-> dequeue? boolean?)]
  [dequeue-push-front (-> dequeue? any/c void?)]
  [dequeue-push-back  (-> dequeue? any/c void?)]
  [dequeue-pop-front  (-> nonempty-dequeue/c any/c)]
  [dequeue-pop-back   (-> nonempty-dequeue/c any/c)]))

(struct dequeue-node ([prev #:mutable] [elem #:mutable] [next #:mutable]) #;#:transparent)
(struct dequeue ([front #:mutable] [back #:mutable]) #;#:transparent)

(define empty-dequeue (dequeue null null))

(define (dequeue-empty? q)
  (null? (dequeue-front q)))

(define nonempty-dequeue/c
  (and/c dequeue? (not/c dequeue-empty?)))

(define (dequeue-push-front q x)
  (define new-elem (dequeue-node null x (dequeue-front q))) ;nowy element kolejki: null, wartość i przód
  (if (dequeue-empty? q)
      (set-dequeue-back! q new-elem) ;element do wstawienia jest nowym pierwszym
      (set-dequeue-node-prev! (dequeue-front q) new-elem)) ;jesli nie, wstaw jako wskaznik next zdefiniowany element
  (set-dequeue-front! q new-elem)) ;wstaw wskaznik poczatek kolejki na nowy element

(define (dequeue-push-back q x)
  (define new-elem (dequeue-node (dequeue-back q) x null)) ;nowy element kolejki: tył kolejki, wartość i nulll
  (if (dequeue-empty? q)
      (set-dequeue-front! q new-elem) ;element do wstawienia jest nowym ostatnim
      (set-dequeue-node-next! (dequeue-back q) new-elem)) ;jesli nie, wstaw jako wskaznik prev zdefiniowany element
  (set-dequeue-back! q new-elem)) ;wstaw wskaznik konca kolejki na nowy element

(define/contract (dequeue-pop-front q)
  (-> nonempty-dequeue/c any/c) 
  (define pop-elem (dequeue-front q)) 
  (if (eq? pop-elem (dequeue-back q)) ;jesli element jest jedyny w kolejce
      (set-dequeue-back! q null) ;usuwamy wskaznik na ostatni element
      (set-dequeue-node-prev! (dequeue-node-next pop-elem) null)) ;jesli nie, usuwamy wskaznik ktory wskazywal na pierwszy element
  (set-dequeue-front! q (dequeue-node-next pop-elem)) ;nastepny staje sie nowym pierwszym
  (dequeue-node-elem pop-elem)) ;zwroc wyciagniety z przodu element

(define/contract (dequeue-pop-back q)
  (-> nonempty-dequeue/c any/c)
  (define pop-elem (dequeue-back q))
  (if (eq? pop-elem (dequeue-front q)) 
      (set-dequeue-front! q null) 
      (set-dequeue-node-next! (dequeue-node-prev pop-elem) null)) 
  (set-dequeue-back! q (dequeue-node-prev pop-elem)) 
  (dequeue-node-elem pop-elem))
