#include "compiler.h"
#include "scanner.h"

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
}

} // namespace oevyli