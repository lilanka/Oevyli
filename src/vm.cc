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
  return buffer.constant_pool.item(read_byte());
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

void VM::free_buffer() {
  buffer.instructions.free();
  buffer.constant_pool.free();
  buffer.lines.free();
}

InterpretResult VM::interpret(const char* source) {
  // For testing OpCodes ---------------------------
  int constant = buffer.constant_pool.write_and_get_index(1.2);
  buffer.instructions.write(OP_CONSTANT);
  buffer.instructions.write(constant);
  buffer.lines.write(123);

  constant = buffer.constant_pool.write_and_get_index(3.4);
  buffer.instructions.write(OP_CONSTANT);
  buffer.instructions.write(constant);
  buffer.lines.write(123);

  buffer.instructions.write(OP_ADD);
  buffer.lines.write(123);
  
  constant = buffer.constant_pool.write_and_get_index(5.6);
  buffer.instructions.write(OP_CONSTANT);
  buffer.instructions.write(constant);
  buffer.lines.write(123);

  buffer.instructions.write(OP_DIVIDE);
  buffer.lines.write(123);
  buffer.instructions.write(OP_NEGATE);
  buffer.lines.write(123);

  buffer.instructions.write(OP_RETURN);
  buffer.lines.write(123);

  // TODO (Lilanka): Add support for OP_CONSTANT_LONG

  debug_instructions(&buffer);
  // ------------------------------------------------

  Compiler compiler(source);

  if (!(compiler.compile(&buffer))) {
    buffer.instructions.free();
    return InterpretResult::COMPILE_ERROR;
  }

  ip = buffer.instructions.values;
  debug_printf("%s\n", "passed");
  InterpretResult result = run();

  free_buffer();
  return result;
}

} // namespace Oevyli
