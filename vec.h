#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint32_t u32;

#define RESIZE_MUL 2

/* OPTIONS */

typedef enum {
  OPTION_SOME,
  OPTION_NONE
} option_type;

typedef struct {
  option_type type;
  union {
    u32 val;
  };
} Option;

static inline Option option_none() {
  return (Option){
    .type = OPTION_NONE
  };
}

static inline Option option_some(u32 v) {
  return (Option){
    .type = OPTION_SOME,
    .val = v
  };
}

/* VECTORS */

typedef struct {
  size_t capacity;
  size_t size;
  u32 *data;
} Vec;

typedef enum {
  VEC_OK,
  VEC_ALLOC_ERR,
  VEC_INDEX_OUT_OF_BOUNDS,
  VEC_INVALID_PTR,
  VEC_EMPTY
} vec_result;


vec_result new_vec_capacity(Vec *vec, size_t capacity);

vec_result new_vec(Vec *vec);

vec_result vec_resize(Vec *vec);

vec_result vec_set(Vec *vec, size_t idx, u32 val);

vec_result vec_push(Vec *vec, u32 val);

Option vec_pop(Vec *vec, size_t idx);

Option vec_pop_last(Vec *vec);

void vec_free(Vec *vec);

Option vec_get(Vec vec, size_t idx);

void vec_print(Vec vec);

void vec_print_debug(Vec vec);

vec_result vec_empty(Vec *vec);

vec_result vec_shrink(Vec *vec);
