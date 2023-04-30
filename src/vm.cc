#include <iostream>

#include "vm.h"
#include "compiler.h"

namespace Oevyli {

/*
uint8_t VM::read_byte() {
  return *ip++;
}

InterpretResult VM::run() {
  while (true) {
    uint8_t instruction;
    switch (instruction = read_byte()) {
      case OpCode::RETURN: {
        return InterpretResult::INTERPRET_OK;
      }
    } 
  }  
  return InterpretResult::INTERPRET_OK;
}
*/

InterpretResult VM::interpret(const char* source) {
  ip = instructions.code;
  Compiler compiler(source, instructions);
  //run();

  // Compiler fill the instr with bytecode
  if (!compiler.compile()) {
    // deallocate instr
    return InterpretResult::INTERPRET_COMPILE_ERROR;
  }

  return InterpretResult::INTERPRET_OK;
}

} // namespace Oevyli
