#include <string>

#include "vm.h"
#include "debug.h"

namespace Oevyli {

InterpretResult VM::interpret(const char* source) {
  // For testing OpCodes ---------------------------
  int constant = constant_pool.write_and_get_index(1.2);
  instructions.write(OP_CONSTANT);
  instructions.write(constant);
  lines.write(0);

  constant = constant_pool.write_and_get_index(1.5);
  instructions.write(OP_CONSTANT);
  instructions.write(constant);
  lines.write(1);

  instructions.write(OP_RETURN);
  lines.write(2);

  // TODO (Lilanka): Add support for OP_CONSTANT_LONG

  debug_instructions(instructions, constant_pool, lines);
  // ------------------------------------------------

  return InterpretResult::OK;
}

} // namespace Oevyli
