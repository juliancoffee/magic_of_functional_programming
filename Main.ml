(* currying *)
let f a = fun b -> a + b

(* kind of currying, but not all the time, here we use fun a b, which also
   expects two arguments 

   if we wanted to write our f in normal way, we would use following
    let f a b = a + b
   and it would behave identically, so you could call it like
    f 5
   and get function that "rememberes" 5 and expects value to evaluate fully
   *)
let g func = fun a b -> func a b
