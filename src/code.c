#include <stdlib.h>

#include "code.h"

void init_code(Code* code) {
  code->count = 0;
  code->capacity = 0;
  code->code = NULL;
}

void append_code(Code* code, uint8_t byte) {
  if (code->capacity < code->count + 1) {
    int old_capacity = code->capacity;
    code->capacity = oli_grow_capacity(old_capacity);
    code->code = oli_grow_vector(uint8_t, code->code, old_capacity, code->capacity);
  }
  code->code[code->count] = byte;
  code->count++;
}