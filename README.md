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
```
