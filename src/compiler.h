#ifndef COMPILER_H
#define COMPILER_H

#include "common.h"
#include "instr.h"
#include "scanner.h"

namespace Oevyli {

// Parsing and Code generation happens here
class Compiler {
public:
  Compiler(const char* source): scanner(source) {};

  // Compilation starts here. It takes the source file as input
  // and do the compilation and running 
  bool compile(Instr& instructions);

private:
  // Advancing through tokens
  void advance();
  // Similar to advance(), but validates if current token has expected type 
  void consume(TokenType type, const char* message);
  void expression();
  // Tell the user about error tokens
  void error_at_current(const char* message);
  // Tell user about error of previos token
  void error(const char* message);

  void error_at(Token& token, const char* message);

private:
  Scanner scanner;
  Token previous;
  Token current;
  bool had_error = false;   // If there are errors in compilation stage
  bool panic_mode = false;  // To avoid error cascades
};

} // namespace Oevyli

#endif
