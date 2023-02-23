#include "compile.h"
#include "scanner.h"

#include "debug.h"

namespace oevyli {

Compile::Compile(const char* source) {
  Scanner scanner{source};

  // Generate tokens
  while (true) {
    Token token = scanner.tokenize();

    if (token.type == TokenType::TEOF)
      break;
  }
}

} // namespace oevyli