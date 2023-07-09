#lang racket

(provide (struct-out column-info)
         (struct-out table)
         (struct-out and-f)
         (struct-out or-f)
         (struct-out not-f)
         (struct-out eq-f)
         (struct-out eq2-f)
         (struct-out lt-f)
         table-insert
         table-project
         table-sort
         table-select
         table-rename
         table-cross-join
         table-natural-join)

(define-struct column-info (name type) #:transparent)

(define-struct table (schema rows) #:transparent)

(define cities
  (table
   (list (column-info 'city    'string)
         (column-info 'country 'string)
         (column-info 'area    'number)
         (column-info 'capital 'boolean))
   (list (list "Wrocław" "Poland"  293 #f)
         (list "Warsaw"  "Poland"  517 #t)
         (list "Poznań"  "Poland"  262 #f)
         (list "Berlin"  "Germany" 892 #t)
         (list "Munich"  "Germany" 310 #f)
         (list "Paris"   "France"  105 #t)
         (list "Rennes"  "France"   50 #f))))

(define countries
  (table
   (list (column-info 'country 'string)
         (column-info 'population 'number))
   (list (list "Poland" 38)
         (list "Germany" 83)
         (list "France" 67)
         (list "Spain" 47))))

(define (empty-table columns) (table columns '()))

; Wstawianie

(define (table-insert row tab)
  (define (compare w1 w2)
    (define (compare-pom t f) ;funkcja pomocnicza do porownywania
      (and (equal? (column-info-type (car w2)) t) 
           (f (car w1))))
    (if (null? w2) #t ;porownywanie wedlug typow
        (cond [(compare-pom 'string string?) (compare (cdr w1) (cdr w2))]
              [(compare-pom 'number number?) (compare (cdr w1) (cdr w2))]
              [(compare-pom 'boolean boolean?) (compare (cdr w1) (cdr w2))]
              [(compare-pom 'symbol symbol?) (compare (cdr w1) (cdr w2))]
              [else #f])))
  (if (= (length (table-schema tab)) (length row)) ;wyszukiwanie ewentualnych errorow (typy lub liczba kolumn)
      (if (compare row (table-schema tab))
          (table (table-schema tab) (cons row (table-rows tab)))
          (error "Nieodpowiedni typ argumentow"))
      (error "Nieodpowiednia ilosc argumentow")))
          
; Projekcja

(define (table-project cols tab)
  (define (in nazwa schemat) ;sprawdzanie czy istnieje kolumna "nazwa"
    (if (null? schemat)
        #f
        (if (equal? nazwa (column-info-name (car schemat)))
            #t
            (in nazwa (cdr schemat)))))
  (define (schemat-w nazwa schemat) ; zwrocenie wiersza z nazwa
    (if (null? schemat)
        (error "Nie ma takiej nazwy")
        (if (equal? nazwa (column-info-name (car schemat)))
            (car schemat)
            (schemat-w nazwa (cdr schemat)))))
  (define (nowy-schemat cols schemat) ;tworzenie nowego schematu na bazie wierszy z nazwa
    (if (null? cols)
        null
        (if (in (car cols) schemat)
            (cons (schemat-w (car cols) schemat) (nowy-schemat (cdr cols) schemat))
            (nowy-schemat cols schemat))))
  (define (return-elem nazwa schemat wiersz) ;zwrocenie elementu na bazie wiersza i schematu
    (if (null? schemat)
        null
        (if (equal? nazwa (column-info-name (car schemat)))
            (car wiersz)
            (return-elem nazwa (cdr schemat) (cdr wiersz)))))
  (define (nowy-wiersz cols schemat wiersz) ;tworzenie nowego wiersza do projekcji
    (if (null? cols)
        null
        (cons (return-elem (car cols) schemat wiersz) (nowy-wiersz (cdr cols) schemat wiersz))))
  (define (nowa-tabela cols schemat wiersze) ;tworzenie nowej tabeli do projekcji
    (if (null? wiersze)
        null
        (cons (nowy-wiersz cols schemat (car wiersze)) (nowa-tabela cols schemat (cdr wiersze)))))
  (if (null? cols) ;projekcja
      (empty-table null)
      (table (nowy-schemat cols (table-schema tab)) (nowa-tabela cols (table-schema tab) (table-rows tab)))))
  
; Sortowanie

(define (table-sort cols tab)
  (define (get-val nazwa wiersz schemat) ;wartosc
    (if (null? wiersz)
      (error "Nie znaleziono")
      (if (equal? nazwa (column-info-name (car schemat)))
          (car wiersz)
          (get-val nazwa (cdr wiersz) (cdr schemat)))))
  (define (compare-types cols w1 w2 schemat) ;komparator dla poszczegolnych typow
    (define (compare-value wart1 wart2) 
    (cond [(and (string? wart1) (string? wart2)) (string<? wart1 wart2)]
          [(and (number? wart1) (number? wart2)) (< wart1 wart2)]
          [(and (symbol? wart1) (symbol? wart2)) (symbol? wart1 wart2)]
          [(and (boolean? wart1) (boolean? wart2)) (and (not wart1) wart2)]))
    (cond [(null? cols) #f]
          [(compare-value (get-val (car cols) w1 schemat) (get-val (car cols) w2 schemat)) #t]
          [(equal? (get-val (car cols) w1 schemat) (get-val (car cols) w2 schemat)) (compare-types (cdr cols) w1 w2 schemat)]
          [else #f]))     
  (define (insert n xs cols tab)
    (if (null? xs)
      (list n)
      (if (compare-types cols n (car xs) (table-schema tab))
          (cons n xs)
          (cons (car xs) (insert n (cdr xs) cols tab)))))
  (define (insertion-sort tab cols)
    (define (it xs ys)
      (if (null? xs)
          ys
          (it (cdr xs) (insert (car xs) ys cols tab))))
    (it (table-rows tab) null))
  (table (table-schema tab) (insertion-sort tab cols)))

; Selekcja

(define-struct and-f (l r))
(define-struct or-f (l r))
(define-struct not-f (e))
(define-struct eq-f (name val))
(define-struct eq2-f (name name2))
(define-struct lt-f (name val))

(define (table-select form tab)
  (define (eq-f-test nazwa wart wiersz tab) ;ewentualny error zwiazany z eq-f
    (if (null? wiersz)
        (error "Nie ma takiej kolumny")
        (if (equal? (column-info-name (car tab)) nazwa)
            (if (equal? wart (car wiersz))
                #t
                #f)
            (eq-f-test nazwa wart (cdr wiersz) (cdr tab)))))
  (define (eq2-f-test nazwa wiersz tab) ;ewentualny error zwiazany z eq2-f
    (if (null? wiersz)
        (error "Nie ma takiej kolumny")
        (if (equal? nazwa (column-info-name (car tab)))
            (car wiersz)
            (eq2-f-test nazwa (cdr wiersz) (cdr tab)))))
  (define (lt-f-test nazwa wart wiersz tab) ;ewentualny error zwiazany z lt-f
    (if (null? wiersz)
        (error "Nie ma takiej kolumny")
        (if (equal? nazwa (column-info-name (car tab)))
            (if (< (car wiersz) wart)
                #t
                #f)
            (lt-f-test nazwa wart (cdr wiersz) (cdr tab)))))
  (define (eval form wiersz tab) ;sprawdzanie wszystkich struktur
    (cond [(and-f? form) (and (eval (and-f-l form) wiersz tab) (eval (and-f-r form) wiersz tab))]
          [(or-f? form) (or (eval (or-f-l form) wiersz tab) (eval (or-f-r form) wiersz tab))]
          [(not-f? form) (not (eval (not-f-e form) wiersz tab))]
          [(eq-f? form) (eq-f-test (eq-f-name form) (eq-f-val form) wiersz tab)]
          [(eq2-f? form) (equal? (eq2-f-test (eq2-f-name form) wiersz tab)
                                 (eq2-f-test (eq2-f-name2 form) wiersz tab))]
          [(lt-f? form) (lt-f-test (lt-f-name form) (lt-f-val form) wiersz tab)]))
  (define (eval-table form wiersz tab) ;tworzenie tabeli selekcji
    (if (null? wiersz)
        null
        (if (eval form (car wiersz) (table-schema tab))
            (cons (car wiersz) (eval-table form (cdr wiersz) tab))
            (eval-table form (cdr wiersz) tab))))
  (table (table-schema tab) (eval-table form (table-rows tab) tab)))

; Zmiana nazwy

(define (table-rename col ncol tab)
  (define (zmiana nazwa nazwa2 schemat)
    (if (null? schemat)
        (error "Brak kolumn")
        (if (equal? (column-info-name (car schemat)) nazwa)
            (cons (column-info nazwa2 (column-info-type (car schemat))) (cdr schemat))
            (cons (car schemat) (zmiana nazwa nazwa2 (cdr schemat))))))
  (table (zmiana col ncol (table-schema tab)) (table-rows tab)))

; Złączenie kartezjańskie

(define (table-cross-join t1 t2)
  (define (w-join w1 w2 curr)
    (if (or (null? w1) (null? w2))
        null
        (if (null? curr)
            (w-join (cdr w1) w2 w2)
            (cons (append (car w1) (car curr))
                  (w-join w1 w2 (cdr curr))))))
  (table (append (table-schema t1) (table-schema t2)) (w-join (table-rows t1) (table-rows t2) (table-rows t2))))

; Złączenie

(define (table-natural-join t1 t2)
  (define (dup t1-schema t2-schema) ;tworzy liste nazw
    (define (get-elem nazwa schemat) ;zwraca element o danej nazwie
      (if (null? schemat)
          #f
          (if (equal? nazwa (column-info-name (car schemat)))
              #t
              (get-elem nazwa (cdr schemat)))))
    (define (make-list t1-schema t2-schema) ;funkcja pomocnicza do tworzenia list
      (if (null? t1-schema)
          null
          (if (get-elem (column-info-name (car t1-schema)) t2-schema)
              (cons (cons (column-info-name (car t1-schema)) (string->symbol (string-append (symbol->string (column-info-name (car t1-schema))) "1"))) (make-list (cdr t1-schema) t2-schema))
              (make-list (cdr t1-schema) t2-schema))))
    (make-list (table-schema t1) (table-schema t2)))
  (define (rename-dup t2 l) ;zmiana nazwy
    (if (null? l)
        t2
        (table-rename (car (car l)) (cdr (car l)) (rename-dup t2 (cdr l)))))
  (define (create-form l) ;formula do select
    (if (null? (cdr l))
        (eq2-f (car (car l)) (cdr (car l)))
        (and-f (eq2-f (car (car l)) (cdr (car l))) (create-form (cdr l)))))
  (define (unique-list schemat l) ;lista bez powtorzen
    (define (to-include nazwa l)
      (if (null? l)
          #t
          (if (equal? nazwa (cdr (car l)))
              #f
              (to-include nazwa (cdr l)))))
    (if (null? schemat)
        null
        (if (to-include (column-info-name (car schemat)) l)
            (cons (column-info-name (car schemat)) (unique-list (cdr schemat) l))
            (unique-list (cdr schemat) l))))
  (define (natural-join-1 t1 t2 l) ;pomocnicze procedury laczace proces w calosc
    (define (natural-join-pom t1 t2 l) 
      (table-project (unique-list (append (table-schema t1) (table-schema t2)) l)
                   (table-select (create-form l) (table-cross-join t1 t2))))
    (if (null? l)
        (table-cross-join t1 t2)
        (natural-join-pom t1 (rename-dup t2 l) l)))
  (natural-join-1 t1 t2 (dup t1 t2)))

; Testy
;(table-rows (table-insert (list "Barcelona" "Spain" 162 #f) cities))
;(table-project '(city area) cities)
;(table-rename 'city 'asdf cities)
;(table-rows (table-sort '(country city) countries))
;(table-rows (table-select (and-f (eq-f 'capital #t) (not-f (lt-f 'area 300))) cities))
;(table-cross-join cities (table-rename 'country 'country2 countries))
;(table-natural-join cities countries)
