#include <stdio.h>

// adder type that emulates closure
//
// step is our captured environment
struct adder_t {
  size_t step;
};

// function that does actual work
//
// let's define a convention to use the name of our
// closure type with prefix call_
size_t call_adder_t(struct adder_t obj, size_t n) {
  return n + obj.step;
}

// helper to create our adder
struct adder_t create_adder(size_t step) {
  struct adder_t obj = { .step = step };
  return obj;
}

// helper to call our adder
// ## prefixes our type with call_
#define CALL(closure_type) call_ ## closure_type

// our incrementer
struct adder_t increment(void) {
  // step is 1 now
  return create_adder(1);
}

int main(void) {
  // one important notice, closure is not a function
  //
  // some languages hide it for you, some don't
  struct adder_t inc = increment();

  printf("%ld\n", CALL(adder_t)(inc, 5));
}
