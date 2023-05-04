#include <stdlib.h>
#include <stdio.h>

struct closure_t {
  // generic environment
  void* env;
  // generic closure-function pointer
  // first argument is closure itself
  void* (*call)(struct closure_t, void*);
};

// creator function
struct closure_t create_closure(void* env, void* (*f)(struct closure_t, void*)) {
  struct closure_t obj = { .env = env, .call = f };
  return obj;
}

/* p. s.
because we write in C, we also need to write destruction function
to free all resources, but please don't make me do it
*/

// call helper (not a macro this time!)
void* do_call(struct closure_t obj, void* args) {
  // note, we have to type obj twice
  //
  // in most object oriented languages, "self" or "this"
  // is passed implicitly, but in C we need to do it ourselves
  return obj.call(obj, args);
}

// Adder
//
// Closure that adds captured value to all arguments and returns a new array.
// everything as one array.

// Our requirement is that closure can have only one arguments, but because
// C doesn't have a vector type, we also need to pass the size of our array.
//
// So let us make vector type ourselves.
struct int_list_t {
  size_t n;
  int* list;
};

int* add_to_all(struct closure_t obj, struct int_list_t* list) {
  // sanity check
  if (!list || !obj.env) {
    return NULL;
  }

  const size_t n = (*list).n;
  const int* args = (*list).list;
  const int step = *(int*)(obj.env);

  int* res = malloc(sizeof(int) * n);

  // do actual work
  for (size_t counter = 0; counter < n; counter++) {
    res[counter] = args[counter] + step;
  }

  return res;
}

int* mul_all(struct closure_t obj, struct int_list_t* list) {
  // sanity check
  if (!list || !obj.env) {
    return NULL;
  }

  const size_t n = (*list).n;
  const int* args = (*list).list;
  const int step = *(int*)(obj.env);

  int* res = malloc(sizeof(int) * n);

  // do actual work
  for (size_t counter = 0; counter < n; counter++) {
    res[counter] = args[counter] * step;
  }

  return res;
}

// type erasure
#define CAST(f) (void* (*)(struct closure_t, void*))f

struct closure_t add1(void) {
  // create box for our env by allocating memory for it
  int* env = malloc(sizeof(int));
  // populate it
  *env = 1; 

  return create_closure(env, CAST(&add_to_all));
}

struct closure_t add10(void) {
  int* env = malloc(sizeof(int));
  *env = 10; 

  return create_closure(env, CAST(&add_to_all));
}

struct closure_t sub10(void) {
  int* env = malloc(sizeof(int));
  *env = -10;

  return create_closure(env, CAST(&add_to_all));
}

struct closure_t mul_by_10(void) {
  int* env = malloc(sizeof(int));
  *env = 10;

  return create_closure(env, CAST(&mul_all));
}

void print_args(struct int_list_t args) {
  size_t n = args.n;
  printf("size: %ld\n", n);

  for (size_t counter = 0; counter < n; counter++) {
    printf("%d ", args.list[counter]);
  }
  printf("\n\n");
}

// this can be generalized to all types, similar to how qsort works
//
// void* map(void* start, size_t n, size_t size, struct closure_t f)
//
// but that's the territory of C magic and not the topic of this talk
//
// `f` is expected to be fn(int*) -> int*
int* map(struct int_list_t list, struct closure_t f) {
  size_t n = list.n;
  int* els = list.list;

  int* res = malloc(sizeof(int) * n);
  for (size_t counter = 0; counter < n; counter++) {
    // (ab)using pointer arithmetic
    res[counter] = *(int*)do_call(f, els + counter);
  }

  return res;
}

// `f` is expected to be fn(int*) -> ()
void for_each(struct int_list_t list, struct closure_t f) {
  size_t n = list.n;
  int* els = list.list;

  for (size_t counter = 0; counter < n; counter++) {
    do_call(f, els + counter);
  }
}

int main(void) {
  const size_t N = 9;

  // create our list
  int* list = malloc(sizeof(int) * N);
  for (size_t counter = 0; counter < N; counter++) {
    list[counter] = counter;
  }
  struct int_list_t args = {.n = N, .list = list};

  // show
  print_args(args);

  // we don't free anything, because it's end of a program anyway
  struct int_list_t res1 = {.list = do_call(add1(), &args), .n = N};
  struct int_list_t res2 = {.list = do_call(add10(), &args), .n = N};
  struct int_list_t res3 = {.list = do_call(sub10(), &args), .n = N};
  struct int_list_t res4 = {.list = do_call(mul_by_10(), &args), .n = N};

  print_args(res1);
  print_args(res2);
  print_args(res3);
  print_args(res4);

  return printf("hello\n");
}
