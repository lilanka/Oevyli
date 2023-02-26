#include "compiler.h"
#include "scanner.h"
#include "parser.h"

#include "common.h"
#include "debug.h"

namespace oevyli {

Compiler::Compiler(const char* source) {
  Scanner scanner{source};
  Parser parser;

  // Generate tokens
  while (true) {
    Token token = scanner.tokenize();
    Tree parse_tree = parser.generate_parse_tree(token);
    //debug_token(token);

    if (token.type == TokenType::TEOF)
      break;
  }

  OEVYLI_MESSAGE("Compilation success.");
}

} // namespace oevyli