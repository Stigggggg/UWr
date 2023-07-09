#lang plait

;skladnia

(define-type Program
  (programE [flist : (Listof Function)] [e : Exp]))

(define-type Function
  (funcE [id : Symbol] [args : (Listof Symbol)] [e : Exp]))

(define-type Exp
  (numE [n : Number])
  (varE [x : Symbol])
  (opE [l : Exp] [op : Op] [r : Exp])
  (ifE [b : Exp] [l : Exp] [r : Exp])
  (letE [x : Symbol] [e1 : Exp] [e2 : Exp])
  (funE [f : Symbol] [args : (Listof Exp)]))

(define-type Op
  (add) (sub) (mul) (leq))

;parser

(define (parse-prog [p : S-Exp]) : Program
  (cond
    [(s-exp-match? `{define {ANY ...} for ANY} p)
     (programE (let ([fs (map parse-func (s-exp->list (second (s-exp->list p))))])
                 (if (unique? (map funcE-id fs))
                     fs
                     (error 'parse-prog "function names are repeating")))
               (parse-exp (fourth (s-exp->list p))))]
    [else (error 'parse-prog "syntax error: program")]))

(define (parse-func [f : S-Exp]) : Function
  (cond
    [(s-exp-match? `[fun SYMBOL (SYMBOL ...) = ANY] f)
     (funcE (s-exp->symbol (second (s-exp->list f)))
            (let ([args (map s-exp->symbol (s-exp->list (third (s-exp->list f))))])
              (if (unique? args)
                  args
                  (error 'parse-func "args names are repeating")))
            (parse-exp (list-ref (s-exp->list f) 4)))]
    [else (error 'parse-func "syntax error: function")]))
          
(define (parse-exp [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [(s-exp-match? `{ANY SYMBOL ANY} s)
     (opE (parse-exp (first (s-exp->list s)))
          (parse-op (s-exp->symbol (second (s-exp->list s))))
          (parse-exp (third (s-exp->list s))))]
    [(s-exp-match? `{ifz ANY then ANY else ANY} s)
     (ifE (parse-exp (second (s-exp->list s)))
          (parse-exp (fourth (s-exp->list s)))
          (parse-exp (list-ref (s-exp->list s) 5)))]
    [(s-exp-match? `{let SYMBOL be ANY in ANY} s)
     (letE (s-exp->symbol (second (s-exp->list s)))
           (parse-exp (fourth (s-exp->list s)))
           (parse-exp (list-ref (s-exp->list s) 5)))]
    [(s-exp-match? `{SYMBOL {ANY ...}} s)
     (funE (s-exp->symbol (first (s-exp->list s)))
           (map parse-exp (s-exp->list (second (s-exp->list s)))))]
    [else (error 'parse-exp "syntax error: exp")]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(equal? op '+) (add)]
    [(equal? op '-) (sub)]
    [(equal? op '*) (mul)]
    [(equal? op '<=) (leq)]
    [else (error 'parse-op "syntax error: operator")]))

(define (unique? [xs : (Listof Symbol)]) : Boolean
  (type-case (Listof Symbol) xs
    [empty #t]
    [(cons x xs)
     (if (member x xs)
         #f
         (unique? xs))]))

;value i srodowisko

(define-type-alias Value Number)

(define-type Func-close
  (f-close [args : (Listof Symbol)] [e : Exp] [env : Env]))

(define-type Storable
  (valS [v : Value])
  (funcS [f : Func-close])
  (undefS))

(define-type Binding
  (bind [name : Symbol]
        [ref : (Boxof Storable)]))

(define-type-alias Env (Listof Binding))

(define mt-env empty)

(define (extend-env-undef [env : Env] [x : Symbol]) : Env
  (cons (bind x (box (undefS))) env))

(define (extend-env [env : Env] [x : Symbol] [v : Value]) : Env
  (cons (bind x (box (valS v))) env))

(define (find-var [env : Env] [x : Symbol]) : (Boxof Storable)
  (type-case (Listof Binding) env
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? x (bind-name b))
                         (bind-ref b)]
                        [else
                         (find-var rst-env x)])]))
  
(define (lookup-env [x : Symbol] [env : Env]) : Value
  (type-case Storable (unbox (find-var env x))
    [(valS v) v]
    [(funcS f)
     (error 'lookupenv "no functions allowed in this env")]
    [(undefS) (error 'lookup-env "undefined variable")]))

(define (lookup-env-func [env : Env] [x : Symbol]) : Func-close
  (type-case Storable (unbox (find-var env x))
    [(funcS f) f]
    [(valS v) (error 'lookup-env-func "no variables allowed in this env")]
    [(undefS) (error 'lookup-env-func "undefined variable")]))
    
(define (update-env! [env : Env] [id : Symbol] [args : (Listof Symbol)] [e : Exp] [envf : Env]) : Void
  (set-box! (find-var env id) (funcS (f-close args e envf))))

;ewaluacja

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(leq) (lambda (x y) (if (<= x y) 0 42))]))

(define (eval [p : Program]) : Value
 (type-case Program p
   [(programE fs e)
    (let ([new-env (foldr (lambda (f env) (extend-env-undef env (funcE-id f))) mt-env fs)])
      (begin
        (foldr (lambda (f fs) (type-case Function f
                                [(funcE id args e)
                                 (update-env! new-env id args e new-env)]))
               (void)
               fs)
        (eval-exp e new-env)))]))

(define (eval-exp [e : Exp] [env : Env]) : Value
  (type-case Exp e
    [(numE n) n]
    [(varE x) (lookup-env x env)]
    [(opE e1 op e2) ((op->proc op) (eval-exp e1 env) (eval-exp e2 env))]
    [(ifE e0 e1 e2)
     (if (= (eval-exp e0 env) 0)
         (eval-exp e1 env)
         (eval-exp e2 env))]
    [(letE x e1 e2)
     (eval-exp e2 (extend-env env x (eval-exp e1 env)))]
    [(funE f args)
     (apply (lookup-env-func env f) (map (lambda (e) (eval-exp e env)) args))]))

(define (apply [f : Func-close] [args : (Listof Value)]) : Value
  (type-case Func-close f
    [(f-close xs e env)
     (eval-exp e (foldr (lambda (x env) (extend-env env (fst x) (snd x)))
                        env
                        (map2 pair xs args)))]))

(define (run [s : S-Exp]) : Value
  (eval (parse-prog s)))

;testy

(module+ test
  (print-only-errors #t))

(module+ test
  (test (run `{define
                 {[fun fact (n) = {ifz n then 1 else {n * {fact ({n - 1})}}}]}
                for
                 {fact (5)}}) 120)
  (test (run `{define
                {[fun even (n) = {ifz n then 0 else {odd ({n - 1})}}]
                 [fun odd (n) = {ifz n then 42 else {even ({n - 1})}}]}
                for
                 {even (1024)}}) 0)
  (test (run `{define
                {[fun gcd (m n) = {ifz n then m else {ifz {m <= n}
                                                          then {gcd (m {n - m})}
                                                          else {gcd ({m - n} n)}}}]}
                for
                 {gcd (81 63)}}) 9))
 

                