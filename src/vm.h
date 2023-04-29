#ifndef VM_H
#define VM_H

#include "common.h"

namespace Oevyli {

enum class InterpretResult {
  INTERPRET_OK,
};

class VM {
public:
  VM() {}

  // After getting source code, this function executes the main pipeline.
  // Scane -> Compile -> Execute
  InterpretResult interpret(const char* source);

};

} // namespace Oevyli

#endif
