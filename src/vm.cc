#include "vm.h"
#include "compiler.h"
#include "instr.h"

namespace Oevyli {

InterpretResult VM::interpret(const char* source) {
  Instr instructions;
  Compiler compiler(source);

  // Compiler fill the instr with bytecode
  if (!compiler.compile(instructions)) {
    // deallocate instr
    return InterpretResult::INTERPRET_COMPILE_ERROR;
  }
  return InterpretResult::INTERPRET_OK;
}

} // namespace Oevyli
