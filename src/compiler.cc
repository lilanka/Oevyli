#include "compiler.h"
#include "scanner.h"

#include "common.h"
#include "debug.h"

namespace oevyli {

Compiler::Compiler(const char* source) {
  Scanner scanner{source};

  // Generate tokens
  while (true) {
    Token token = scanner.tokenize();

    debug_token(token);

    if (token.type == TokenType::TEOF)
      break;
  }

  OEVYLI_MESSAGE("Compilation success.");
}

} // namespace oevyli