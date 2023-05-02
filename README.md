# Preparation
I expect you to have OCaml, Clojure and C compiler (GCC) installed.
And that you're running GNU/Linux. Later is not required, but in that case,
you'll need to compile C with your own compiler.

If you don't have some of it, it shouldn't be too hard to install.
Or you can try to use online tools.

May the Force be with you.

# Ocaml instructions

Used to explain higher-order functions.
```ocaml
(* # is required, it's a directive *)
#use "Main.ml";;

(g f) 3 4;;

(* we can use different types too *) 
let conc a b = a ^ b;;
(g conc) "hello" "world";;

(* and when I say different I mean it *)
include List;;

let fits l cap = List.length l <= cap;;
(g fits)
(* it shows '_weak1 instead of 'a, because it can't say which type we want,
but it's not generic anymore. *)

(* you can try to assign it to variable like that

let fits_new = (g fits);;
you'll get type '_weak again, but when you call it with something

fits_new [5; 5];;
fits_new will stick to (int list -> int -> bool) which means that it expects
list of ints, then int and then it will return a boolean
*)

(* yeah, this is a function too *)
(g fits) [5; 5];;

(g fits) [5; 5] 1;;
(g fits) [5; 5] 3;;
(g fits) [5; 5] 2;;

(* btw, our g is (almost) an identity function, because it basically returns
its argument (func). You can see it from signature.
    g: ('a -> 'b -> 'c) -> 'a -> 'b -> 'c

Which means that we can call our `fits` function just as is and get identical
result
*)

fits [5; 5] 2;;

(* extras *)
bigger_positives [-5; 4; 5]
```

# C instructions
```bash
$ make
$ ./main
$ ./closure
```

# Clojure instructions

```clojure
(load-file "core.clj")

(eval answer-1)
(eval answer-2)
(eval answer-3)
(eval answer-4)
(eval answer-5)
(eval answer-6)
(eval answer)

extra-let
unlet
```
