#ifndef INSTR_H
#define INSTR_H

#include <cinttypes>

#include "common.h"

namespace Oevyli {

enum class OpCode {
  RETURN, 
};

// Instructions that executud by the VM
class Instr {
public:
  int count;
  int capacity;
  uint8_t* code;

  Instr(): count(0), capacity(0), code(nullptr) {}
  ~Instr() {}
  
  // Write on dynamic array
  void write(uint8_t byte);
  void free();
};

} // namespace Oevyli

#endif
