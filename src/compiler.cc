#include <iostream>

#include "compiler.h"
#include "scanner.h"

namespace Oevyli {

// TODO (Lilanka): It's allway wise to free the memory. 
// After the tokenization part source should be freed.
// And there is no point storing all the tokens at once. 
// So we request a token only when scanner needs one 
void Compiler::compile(const char* source) {
  Scanner scanner(source);

  int line = -1;
  bool scanning = true;
  while (scanning) {
    Token token = scanner.tokanize();
    if (token.line != line) {
      line = token.line;
      std::cout << token.line << std::endl;
    } else {
      std::cout << "  | ";
    }
 
    // We don't have this much of wrapper just yet
    std::cout << token.length << " " << token.start;

    if (token.type == TokenType::T_ERROR) {
      //scanning = false;
      std::cout << "Unrecorgnized token" << std::endl;
    } else if (token.type == TokenType::T_EOF) {
      scanning = false;
      std::cout << "Scanning finished" << std::endl;
    }
  }
}

} // namespace Oevyli
