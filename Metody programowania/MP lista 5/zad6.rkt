#lang plait

(define-type (RoseTree 'a)
  (leaf [elem : 'a])
  (node [children : (Listof (RoseTree 'a))]))


(define example-rose
  (node (list (leaf "A")
              (node (list (leaf "B")
                          (leaf "C")))
              (leaf "D")
              (node (list (node (list (leaf "E")
                                       (leaf "F")))
                          (leaf "G"))))))



(define (show-rose [r : (RoseTree 'a)]) : (Listof 'a)
  (local
    ;funkcja do łączenia listy list w jedą listę
    [(define (list-flatten [l : (Listof (Listof 'a))]) : (Listof 'a)
       (if (empty? l)
           '()
           (append (first l) (list-flatten (rest l)))))]

  (cond
    ;jak dotrzemy do liścia zwracamy listę jednoelementową
    [(leaf? r) (list (leaf-elem r))]
    [else
     ; wpp robimy jedną listę z połączonych elementów od lewej strony
     (list-flatten (map show-rose (node-children r)))])))


(show-rose example-rose)

;local sprawia ze mozemy deklarowac funkcje wewnetrzne i nie ma konfliktu typow

;map przechodzi po kolejnych elementach tablicy