#ifndef DEBUG_H
#define DEBUG_H

#include "memory.h"
#include "value.h"
#include "buffers.h"

namespace Oevyli {

extern "C" {
	#include <stdarg.h>
	#include <stdio.h>

	static void debug_printf(const char* format, ...) {
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
}

static void debug_print_value(Value value) {
  debug_printf("%lf\n", value);
}

static void debug_print_string(const char* message) {
  debug_printf("%s\n", message);
}

// To debug VM instructions
static void debug_instructions(InstructionBuffer* buffer) {
  debug_printf("%s\n", "--- Debug Instructions ---");
  debug_printf("%s\n", "| Opcode | Constant Value | Constant Pool Index | Line Number |");
	int pool_idx = 0;
	int n_instructions = 0;
  for (unsigned int i = 0; i < buffer->instructions.size(); ++i) {
    switch (buffer->instructions.item(i)) {
      case OP_CONSTANT: 
				debug_printf("| %s | %f | %i | %i |\n", "OP_CONSTANT", buffer->constant_pool.item(pool_idx), buffer->instructions.item(i+1), buffer->lines.item(n_instructions)); 
				i++; pool_idx++;
				break;
      case OP_CONSTANT_LONG: 
				debug_printf("| %s | %f | %i | %i |\n", "OP_CONSTANT_LONG", buffer->constant_pool.item(pool_idx), buffer->instructions.item(i+1), buffer->lines.item(n_instructions)); 
				i++; 
        pool_idx++;
				break;
      case OP_RETURN: debug_printf("| %s | %s | %s | %i |\n", "OP_RETURN", "nan", "nan", buffer->lines.item(n_instructions)); break;
      default: debug_printf("%s\n", "Unidentefied instruction"); break;
    }
		n_instructions++;
  }
  std::cout << "--- Debug Instructions End! ---" << std::endl;
}

} // namespace Oevyli

#endif
