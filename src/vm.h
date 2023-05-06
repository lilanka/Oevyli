#ifndef VM_H
#define VM_H

#include <cstdint>

#include "opcode.h"
#include "memory.h"
#include "value.h"
#include "buffers.h"

namespace Oevyli {

namespace Constants {
const unsigned int stack_max = 256;
} // namespace Constants

enum class InterpretResult {
  OK,
  COMPILE_ERROR,
  RUNTIME_ERROR
};

class VM {
public:
  VM() {}
  ~VM() {}

  InterpretResult interpret(const char* source);

private:
  InterpretResult run();
  
  // Read instruction about to be executed
  uint8_t read_byte();
  Value read_constant();

  // Compress line information 
  void encode_line_information(int line);
  void decode_line_information(const char* info);

  // Stack ops
  void push(Value value);
  Value pull();

  void free_buffer();

protected:
  InstructionBuffer buffer;

  Value stack[Constants::stack_max]; // This is a stack based VM
  Value* stack_top;

private:
  uint8_t* ip;
};

} // namespace Oevyli

#endif
