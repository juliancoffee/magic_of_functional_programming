(* currying *)
let f a = fun b -> a + b

(* yet another example of higher-order functions

 this one takes a function as parameter and returns a function that takes two
 arguments and applies our function to these parameters

 oh, and this resulting function is curried too, even if we don't do anything *)
let g func = fun a b -> func a b

(* I promised example for currying *)
open List

(* this is completely identical to our f, but we let compiler do the magic *)
let sum x y = x + y
(* yay, we now have x++ from C, except it is sane *)
let inc = sum 1

let bigger_positives l =
    l
    |> List.filter (fun x -> x >= 0) (* this is a function *)
    |> List.map inc (* this too *)
