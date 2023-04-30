#include <iostream>

#include "vm.h"
#include "compiler.h"

namespace Oevyli {

void VM::push(Value value) {
  *stack_top = value;
  stack_top++;
}

Value VM::pull() {
  stack_top--;
  return *stack_top;
}

uint8_t VM::read_byte() {
  return *ip++;
}

Value VM::read_constant() {
  return constant_pool.values[read_byte()];
}

InterpretResult VM::run() {
// TODO (Lilanka): Macros are not good, look for higher order functions
#define BINARY_OP(op)   \
  do {                  \
    double b = pull();  \
    double a = pull();  \
    push(a op b);       \
  } while (false)

  while (true) {
    uint8_t instruction = read_byte();
    switch (instruction) {
      case OP_CONSTANT: {
        Value constant = read_constant(); 
        std::cout << "constant: " << constant << std::endl;
        push(constant);
        std::cout << "top: " << *stack_top << std::endl;
        break;
      }
      case OP_ADD: BINARY_OP(+); break;
      case OP_SUBTRACT: BINARY_OP(-); break;
      case OP_MULTIPLY: BINARY_OP(*); break;
      case OP_DIVIDE: BINARY_OP(/); break;
      case OP_NEGATE: {
        push(-pull());
        std::cout << "negate: " << *stack_top++ << std::endl;
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
#undef BINARY_OP
}

InterpretResult VM::interpret(const char* source) {
  // For testing fill instruction buffer and constant pool buffer 
  instructions.write(OP_CONSTANT);
  constant_pool.write(23.2);
  instructions.write(OP_CONSTANT);
  constant_pool.write(2.2);
  instructions.write(OP_CONSTANT);
  constant_pool.write(200.2);
  instructions.write(OP_NEGATE);
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
