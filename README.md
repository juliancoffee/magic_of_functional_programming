# Idea
Originally I wanted to make a presentation about Y combinator using
spreadsheets, but unfortunately it's not possible within the limitations of
them. So instead this talk was about the magic in functional programming and how to
push some limits.

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

# Links
- [Google Sheet](https://docs.google.com/spreadsheets/d/1cIlxdZlucirXPUvDDPGqKlLHwkydDSwZOOoDGXC2noA/edit#gid=0)
- [Google Slides](https://docs.google.com/presentation/d/14hwra-O6CnYigx4hS4rlihjHDkp8E5cT2NUXzC-Xqas/edit?usp=sharing)
- [YouTube talk](https://youtu.be/TA6t8SQTkAk)
# More
- [Stephen Wolfram on Combinators](https://writings.stephenwolfram.com/2020/12/combinators-and-the-story-of-computation/)
- [Stephen Wolfram on Moses Schonfinkel](https://writings.stephenwolfram.com/2020/12/where-did-combinators-come-from-hunting-the-story-of-moses-schonfinkel/)
- [Python Function Definition](https://github.com/python/cpython/blob/main/Include/cpython/funcobject.h#L36-L60)
- [Python Iterators](https://docs.python.org/3/library/itertools.html)
- [Rust Iterators](https://doc.rust-lang.org/std/iter/index.html)
- [Java Streams](https://docs.oracle.com/javase/8/docs/api/java/util/stream/Stream.html)
# Credits
- [Recursion without Recursion: Python](https://lptk.github.io/programming/2019/10/15/simple-essence-y-combinator.html)
