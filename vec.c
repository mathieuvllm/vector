#include "vec.h"

vec_result new_vec_capacity(Vec *vec, size_t capacity) {
  if (capacity < 4)
    return VEC_ALLOC_ERR;

  vec->capacity = capacity;
  vec->size = 0;
  vec->data = (u32 *)malloc(capacity * sizeof(u32));

  return VEC_OK;
}

vec_result new_vec(Vec *vec) {
  return new_vec_capacity(vec, 8);
}

vec_result vec_resize(Vec *vec) {
  if (!vec)
    return VEC_INVALID_PTR;

  if (vec->capacity > SIZE_MAX / RESIZE_MUL)
    return VEC_ALLOC_ERR;

  size_t new_capacity = vec->capacity * RESIZE_MUL;

  if (new_capacity > SIZE_MAX / sizeof(u32))
    return VEC_ALLOC_ERR;

  u32 *tmp = (u32 *)realloc(vec->data, new_capacity * sizeof(u32));
  if (!tmp)
    return VEC_ALLOC_ERR;

  vec->capacity = new_capacity;
  vec->data = tmp;

  return VEC_OK;
}

vec_result vec_set(Vec *vec, size_t idx, u32 val) {
  if (!vec)
    return VEC_INVALID_PTR;

  if (idx >= vec->size)
    return VEC_INDEX_OUT_OF_BOUNDS;

  vec->data[idx] = val;
  return VEC_OK;
}

 vec_result vec_push(Vec *vec, u32 val) {
   if (!vec)
     return VEC_INVALID_PTR;

   if (vec->size >= vec->capacity) {
     vec_result res = vec_resize(vec);
     if (res != VEC_OK)
       return res;
   }

   vec->size++;
   vec_result r = vec_set(vec, vec->size-1, val);
   if (r != VEC_OK)
     vec->size--;
   return r;
 }

void vec_free(Vec *vec) {
  free(vec->data);
}

Option vec_get(Vec vec, size_t idx) {
   if (idx >= vec.size)
     return option_none();

   u32 val = vec.data[idx];
   return option_some(val);
}

Option vec_pop(Vec *vec, size_t idx) {
  Option ret = vec_get(*vec, idx);
  if (ret.type == OPTION_NONE)
    return ret;

  for (size_t i = 1; idx + i < vec->size; i++) {
    vec->data[idx+i-1] = vec->data[idx+i];
  }

  vec->size--;

  if (vec->capacity >= 4*vec->size)
    vec_shrink(vec);

  return option_some(ret.val);
}

Option vec_pop_last(Vec *vec) {
  return vec_pop(vec, vec->size-1);
}

void vec_print(Vec vec) {
  if (!(vec.data))
    return;
  
  printf("[");
  for (size_t idx = 0; idx < vec.size; idx++) {
    printf("%d", vec.data[idx]);
    if (idx != vec.size-1)
      printf(", ");
  }
  printf("]\n");
}

void vec_print_debug(Vec vec) {
  if (!(vec.data)) {
    printf("Data ptr invalid\n");
    return;
  }

  printf("Capacity: %ld\n", vec.capacity);
  printf("Size: %ld\n", vec.size);
  vec_print(vec);
}

vec_result vec_shrink(Vec *vec) {
  if (!vec)
    return VEC_INVALID_PTR;

  if (vec->size == 0)
    return VEC_EMPTY;

  size_t new_capacity = vec->size;

  u32 *tmp = (u32 *)realloc(vec->data, new_capacity * sizeof(u32));
  if (!tmp)
    return VEC_ALLOC_ERR;

  vec->capacity = new_capacity;
  vec->data = tmp;

  return VEC_OK;
}

vec_result vec_empty(Vec *vec) {
  if (!vec)
    return VEC_INVALID_PTR;
  vec->size = 0;
  return VEC_OK;
}
