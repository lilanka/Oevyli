#ifndef OPCODE_H 
#define OPCODE_H 

namespace Oevyli {

// Opcodes performed by VM
enum OpCode {
  OP_CONSTANT,      // 8-bit constant
  OP_CONSTANT_LONG, // 24-bit constant
  OP_NEGATE,
  // Binary ops
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,

  OP_RETURN,
};

} // namespace Oevyli

#endif
