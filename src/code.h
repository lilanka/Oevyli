// Opcodes for virtual machine

#ifndef CODE_H
#define CODE_H

#include "comm.h"

typedef enum {
  OP_RETURN
} OpCode;

// Code is a sequence of bytecodes
typedef struct {
  int count;
  int capacity;
  uint8_t* code;
} Code;

// Initialize a new code
void init_code(Code* code);

// Append a byte to end of the code
void append_code(Code* code, uint8_t byte);

#endif