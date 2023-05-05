#ifndef VM_H
#define VM_H

#include <cstdint>

#include "opcode.h"
#include "memory.h"
#include "value.h"

namespace Oevyli {

enum class InterpretResult {
  OK,
};

class VM {
public:
  VM() {}
  ~VM() {}

  InterpretResult interpret(const char* source);

private:
  // Compress line information 
  void encode_line_information(int line);
  void decode_line_information(const char* info);

protected:
  // Bytecode instruction that VM executes 
  DMem<uint8_t> instructions;
  // Buffer for Line infromation
  DMem<int> lines;
  // Buffer to store constants 
  DMem<Value> constant_pool;
};

} // namespace Oevyli

#endif
