#ifndef BUFFERS_H
#define BUFFERS_H

#include "memory.h"
#include "value.h"

namespace Oevyli {

struct InstructionBuffer {
	DMem<uint8_t> instructions; // Bytecode instruction that VM executes 
  DMem<int> lines;            // Buffer for Line infromation
  DMem<Value> constant_pool;  // Buffer to store constants 
};

} // namespace Oevyli

#endif
