#include <stdlib.h>
#include <stdio.h>

struct closure_t {
  // generic environment
  void* env;
  // generic closure-function pointer
  void* (*call)(struct closure_t, void*);
};

// creator function
struct closure_t create_closure(void* env, void* (*f)(struct closure_t, void*)) {
  struct closure_t obj = { .env = env, .call = f };
  return obj;
}

// p. s.
// because we write in C, we also need to write destruction function
// to free all resources, but please don't make me do it

// call helper
void* do_call(struct closure_t obj, void* args) {
  return obj.call(obj, args);
}

// Adder
//
// Closure that adds captured value to all arguments and returns a new array.
//
// First argument must state how many arguments we have.
// Others arguments are numbers we want to work with.
// We could create args_t struct, but for simplicity we will just pass
// everything as one array.
int* add_to_all(struct closure_t obj, int* args) {
  // sanity check
  if (!args) {
    return NULL;
  }

  const int n_req = args[0];
  // if no arguments, or number of arguments is negative (??), throw
  if (n_req <= 0) {
    return NULL;
  }
  const size_t n = (size_t)n_req;

  // create result with the same format, because it'll be easier to give
  // an example
  int *res = malloc(sizeof(int) * (n + 1));
  res[0] = n_req;

  int step;
  if (obj.env != NULL) {
    step = *(int*)(obj.env);
  } else {
    // emulate inc() if no step was captured
    step = 1;
  }

  // do actual work
  for (size_t counter = 1; counter < n + 1; counter++) {
    res[counter] = args[counter] + step;
  }

  return res;
}

// type erasure
#define CAST(f) (void* (*)(struct closure_t, void*))f

struct closure_t add1(void) {
  // create box for our env
  int* env = malloc(sizeof(int));
  // populate it
  *env = 1; 

  return create_closure(env, CAST(&add_to_all));
}

struct closure_t add_default(void) {
  return create_closure(NULL, CAST(&add_to_all));
}

struct closure_t add10(void) {
  // create box for our env
  int* env = malloc(sizeof(int));
  // populate it
  *env = 10; 

  return create_closure(env, CAST(&add_to_all));
}

struct closure_t sub10(void) {
  int* env = malloc(sizeof(int));
  *env = -10;

  return create_closure(env, CAST(&add_to_all));
}

// args must be valid, no checks
void print_args(int *args) {
  int n = args[0];
  printf("size: %d\n", args[0]);
  for (int counter = 1; counter < n + 1; counter++) {
    printf("%d ", args[counter]);
  }
  printf("\n");
}

int main(void) {
  const int N = 9;

  // first one for size
  int* args = malloc(sizeof(int) * (N + 1));
  args[0] = N;
  // populate others
  for (int counter = 1; counter < N + 1; counter++) {
    args[counter] = counter;
  }
  // show
  print_args(args);

  struct closure_t adder1 = add1();
  struct closure_t adder_default = add_default();
  struct closure_t adder10 = add10();
  struct closure_t subtractor10 = sub10();

  // we don't free anything, because it's end of a program anyway
  print_args(do_call(adder1, args));
  print_args(do_call(adder_default, args));
  print_args(do_call(adder10, args));
  print_args(do_call(subtractor10, args));

  return printf("hello\n");
}
