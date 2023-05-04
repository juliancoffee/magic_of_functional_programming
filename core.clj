;; clojure creators have slightly different mindset from other languages like
;; OCaml or Haskell.
;; First, clojure doesn't support currying, you need to do it yourself
;; Second, it doesn't force types the same way ones mentioned above 
;;
;; Which is good for us, because original lambda-calculus doesn't have types at
;; all. And currying is explicit.

;; id function, the function that returns its argument
(fn [x] x)

;; if we want to create new definition
(def id
  (fn [x] x))

;; or as a shortcut (see, no fn)
(defn id-new [x] x)

;; currying is explicit
(defn f [a] (fn [b] (+ a b)))

;; our g function
;; 0) define a function g
;; 1) that takes f as argument
;; 2) return a function of a, that returns a function of b
;; 4) that returns an application of f to a (which still a function)
;; 5) and application of resulted function to b
;; 
;; if you didn't understand that, don't worry, this is expected
;; I just wanted to make 1:1 mapping from previous example
(defn g [f]
  (fn [a]
    (fn [b] ((f a) b))))

;; Here Be Dragons
(defn factorial [n]
  (if (zero? n) 1
    (* n (factorial (dec n)))))

;; Clojure also allows you to "quote" expression without evaluating it
(def id-symbol '(fn [x] x))

;; fact references itself, because it's a global name
;; can we do without global names?

;; maybe, but not like this
(def answer-1 '(let
                 [fact (fn [n]
                         (if (zero? n) 1
                           (* n (fact (dec n)))))]
                 (fact 4)))

;; we can't self-refer, let's just pass the function?
(def answer-2 '(let
                 [fact (fn [f] (fn [n]
                                 (if (zero? n) 1
                                   (* n (f (dec n))))))]
                 (fact 4)))

;; yep, but we need to actually pass it
;;
;; important, f also needs to call itself
(def answer-3 '(let
                 [fact (fn [f] (fn [n]
                                 (if (zero? n) 1
                                   (* n ((f f) (dec n))))))]
                 ((fact fact) 4)))

;; we can probably abstract it, but it will make things even worse
(def answer-4 '(let
                 [self-call (fn [f] (f f))
                  fact (self-call
                         (fn [f]
                           (fn [n]
                             (if (zero? n) 1
                               (* n ((self-call f) (dec n)))))))]
                 (fact 4)))

;; this is better, but we still have self-call inside, can we get rid of it?
(def answer-5 '(let
                 [self-call (fn [f] (f f))
                  fact-helper (fn [f] (fn [n]
                                        (if (zero? n) 1
                                          (* n ((self-call f) (dec n))))))
                  fact (self-call fact-helper)]
                 (fact 4)))

;; in fact we can
(def answer-6 '(let
                 [self-call (fn [f] (f f))

                  rec (fn [worker]
                        (self-call (fn [f]
                                     (worker (fn [step] ((self-call f) step))))))

                  fact-helper (fn [self]
                                (fn [n]
                                  (if (zero? n) 1
                                    (* n (self (dec n))))))

                  fact (rec fact-helper)]
                 (fact 4)))

(def answer '(let
                 [
                  self-call (fn [f] (f f))

                  rec (fn [worker]
                        (self-call (fn [step]
                                     (worker (fn [proc]
                                               ((self-call step) proc))))))
                  fact-helper (fn [self]
                                (fn [n]
                                  (if (zero? n) 1
                                    (* n (self (dec n))))))

                  fact (rec fact-helper)
                  expand {
                          ;; let's call rec, by passing our 'worker
                          :worker fact-helper
                          ;; this is what we will get
                          :body1 (self-call
                                  (fn [step]
                                      (fact-helper
                                        (fn [proc]
                                          ((self-call step) proc)))))
                          ;; now let's call fact-helper, by passing 'self
                          :self '(fn [proc] ((self-call step) proc))
                          ;; this is what we will get
                          :body2 (self-call
                                  (fn [step]
                                    (fn [n]
                                       (if (zero? n) 1
                                         (* n (
                                               (fn [proc] ((self-call step) proc))
                                               (dec n)
                                               ))))))
                          ;; now let's call this fn [proc] with our (dec n)
                          :reduced (self-call
                                     (fn [step]
                                       (fn [n]
                                         (if (zero? n) 1
                                           (* n ((self-call step) (dec n)))))))
                          ;; and this is exactly the version from answer-5
                          ;;
                          ;; now you can also inline self-call, if you want
                          ;; but I'll left this as an exercise for the reader :D
                          ;;
                          ;; p. s. I didn't come up with this idea, because
                          ;; this is crazy
                          ;; source https://lptk.github.io/programming/2019/10/15/simple-essence-y-combinator.html
                          }
                  ]
                 ;; now let's try another number to double check
                 (fact 5)))

;; extra
(def extra-let
  (let [ x 5 ] (+ 1 x)))

;; and this is actually used (i know, wow) contrary to recursion magic
;;
;; because while *most* languages support recursion
;; *most* languages don't support let-expression
;;
;; search IIFE JavaScript or IIFE C++
(def unlet ((fn [x] (+ 1 x)) 5))
