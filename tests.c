#include <assert.h>
#include <stdio.h>
#include "vec.h"

int main() {
  Vec vec;
  assert(new_vec(&vec) == VEC_OK);
  assert(vec.size == 0);
  assert(vec.capacity == 8);

  assert(vec_set(&vec, 0, 1) == VEC_INDEX_OUT_OF_BOUNDS);

  assert(vec_push(&vec, 1) == VEC_OK);
  assert(vec.size == 1);
  assert(vec_get(vec, 0).val == 1);

  for (size_t i = 1; i < vec.capacity; i++) {
    assert(vec_push(&vec, 2) == VEC_OK);
  }

  vec_print_debug(vec);

  assert(vec_push(&vec, 0) == VEC_OK);
  assert(vec.capacity == 16);
  assert(vec.size = 8);

  assert(vec_get(vec, 8).type == OPTION_NONE);

  assert(vec_pop(&vec, 0).type == OPTION_SOME);
  assert(vec_pop_last(&vec).type == OPTION_SOME);
  assert(vec_pop(&vec, 2).type == OPTION_SOME);
  assert(vec.size == 5);
  assert(vec_pop(&vec, 6).type == OPTION_NONE);

  vec_print_debug(vec);

  assert(vec_shrink(&vec) == VEC_OK);
  assert(vec.capacity == vec.size);
  vec_print_debug(vec);

  assert(vec_empty(&vec) == VEC_OK);
  assert(vec.size == 0);

  assert(vec_shrink(&vec) == VEC_EMPTY);

  vec_free(&vec);

  Vec vec2;
  assert(new_vec_capacity(&vec2, 128) == VEC_OK);
  for (u32 i = 0; i < 9; i++) {
    assert(vec_push(&vec2, 0) == VEC_OK);
  }

  vec_print_debug(vec2);

  vec_pop_last(&vec2);
  assert(vec2.capacity == vec2.size);
  vec_print_debug(vec2);

  vec_free(&vec2);
  printf("Tests done :)\n");
  return 0;
}
