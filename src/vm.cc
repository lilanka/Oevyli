#include <iostream>

#include "vm.h"
#include "compiler.h"

namespace Oevyli {

uint8_t VM::read_byte() {
  
  return *ip++;
}

Value VM::read_constant() {
  return constant_pool.values[read_byte()];
}

InterpretResult VM::run() {
  while (true) {
    uint8_t instruction;
    switch (instruction = read_byte()) {
      case OP_CONSTANT: {
        Value constant = read_constant(); 
        break;
      }
      case OP_RETURN: {
        return InterpretResult::INTERPRET_OK;
      }
      default:
        return InterpretResult::INTERPRET_RUNTIME_ERROR;
    } 
  }  
  return InterpretResult::INTERPRET_OK;
}

InterpretResult VM::interpret(const char* source) {
  // For testing fill instruction buffer and constant pool buffer 
  instructions.write(OP_CONSTANT);
  constant_pool.write(23.2);
  instructions.write(OP_CONSTANT);
  constant_pool.write(2.2);
  instructions.write(OP_CONSTANT);
  constant_pool.write(200.2);
  instructions.write(OP_RETURN);
  // --------------------------------------

  ip = instructions.values;
  run();
  /*
  Compiler compiler(source, instructions);

  // Compiler fill the instr with bytecode
  if (!compiler.compile()) {
    // deallocate instr
    return InterpretResult::INTERPRET_COMPILE_ERROR;
  }
  */
  return InterpretResult::INTERPRET_OK;
}

} // namespace Oevyli
