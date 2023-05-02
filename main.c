#include <stdio.h>

// adder type that emulates closure
//
// data is our captured environment
// call is our closure-function
struct adder_t {
  size_t data;
  size_t (*call)(struct adder_t, size_t);
};

// to have something to initialize adder with
size_t call_adder(struct adder_t obj, size_t n) {
  return n + obj.data;
}

// helper to create our adder
struct adder_t create_adder(size_t step) {
  struct adder_t obj = { .data = step, .call = &call_adder };
  return obj;
}

// helper to call our adder
size_t do_call(struct adder_t obj, size_t n) {
  // we need to write `obj` twice
  //
  // one to get our `call` function, second to give this `call` function
  // required environment captured in object
  return obj.call(obj, n);
}

// our incrementer
struct adder_t increment(void) {
  return create_adder(1);
}

int main(void) {
  // one important notice, closure is not a function
  //
  // some languages hide it for you, some don't
  struct adder_t inc = increment();

  return printf("%ld\n", do_call(inc, 5));
}
