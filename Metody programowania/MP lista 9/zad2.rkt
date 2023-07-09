#lang racket

;S -> `(Elem) | List
;Elem -> Symbol | Number | String | Cons | Boolean | List | ,Elem | ,@Elem | 'Elem
;List -> `(ListofContent)
;ListofContent -> Elem | Elem Rest
;Rest -> Elem | ListofContent
;Symbol -> 'S
;Number -> n
;String -> "Any_String"
;Cons -> S . S
;Boolean -> #t | #f