#include <string>

#include "vm.h"
#include "debug.h"
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

Value VM::read_constant() {
  return constant_pool.item(read_byte());
}

uint8_t VM::read_byte() {
  return *ip++;
}

InterpretResult VM::run() {
#define BINARY_OP(op)   \
  do {  \
    double b = pull();  \
    double a = pull();  \
    push(a op b);       \
  } while (false)

  while (true) {
    uint8_t instruction;
    switch (instruction = read_byte()) {
      case OP_CONSTANT: {
        Value constant = read_constant();
        push(constant);
        break;
      }
      case OP_NEGATE: push(-pull()); break;
      case OP_ADD:      BINARY_OP(+); break; 
      case OP_SUBTRACT: BINARY_OP(-); break; 
      case OP_MULTIPLY: BINARY_OP(*); break; 
      case OP_DIVIDE:   BINARY_OP(/); break; 
      case OP_RETURN: {
        debug_printf("%f\n", pull());
        return InterpretResult::OK;
      }
    }
  }  
#undef BINARY_OP
}

InterpretResult VM::interpret(const char* source) {
  // For testing OpCodes ---------------------------
  int constant = constant_pool.write_and_get_index(1.2);
  instructions.write(OP_CONSTANT);
  instructions.write(constant);
  lines.write(123);

  constant = constant_pool.write_and_get_index(3.4);
  instructions.write(OP_CONSTANT);
  instructions.write(constant);
  lines.write(123);

  instructions.write(OP_ADD);
  lines.write(123);
  
  constant = constant_pool.write_and_get_index(5.6);
  instructions.write(OP_CONSTANT);
  instructions.write(constant);
  lines.write(123);

  instructions.write(OP_DIVIDE);
  lines.write(123);
  instructions.write(OP_NEGATE);
  lines.write(123);

  instructions.write(OP_RETURN);
  lines.write(123);

  // TODO (Lilanka): Add support for OP_CONSTANT_LONG

  //debug_instructions(instructions, constant_pool, lines);
  // ------------------------------------------------

  Compiler compiler(source);

  if (!(compiler.compile(instructions))) {
    instructions.free();
    return InterpretResult::COMPILE_ERROR;
  }

  ip = instructions.values;
  debug_printf("%s\n", "passed");
  InterpretResult result = run();

  instructions.free();
  lines.free();
  constant_pool.free();
  return result;
}

} // namespace Oevyli
