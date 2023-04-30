#ifndef OPCODES_H
#define OPCODES_H

#include <cinttypes>

#include "common.h"

namespace Oevyli {

enum OpCode: uint8_t {
  OP_CONSTANT,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE,
  OP_RETURN
};

} // namespace Oevyli

#endif
