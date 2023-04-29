#include "vm.h"
#include "compiler.h"

namespace Oevyli {

InterpretResult VM::interpret(const char* source) {
  Compiler compiler;
  compiler.compile(source);
  return InterpretResult::INTERPRET_OK;
}

} // namespace Oevyli
