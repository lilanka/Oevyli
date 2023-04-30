#ifndef VM_H
#define VM_H

#include <cstdint>

#include "instr.h"
#include "common.h"

namespace Oevyli {

enum class InterpretResult {
  INTERPRET_OK,             // Everything good
  INTERPRET_COMPILE_ERROR,  // Compiler throws errors
  INTERPRET_RUNTIME_ERROR  
};

class VM {
public:
  VM() {}
  // After getting source code, this function executes the main pipeline.
  // Scane -> Compile -> Execute
  InterpretResult interpret(const char* source);

private:
  InterpretResult run();
  // Read next byte
  uint8_t read_byte();

protected:
  Instr instructions; // Instructions that VM executes

private:
  uint8_t* ip; // Keeps track of instruction about to be executed
};

} // namespace Oevyli

#endif
