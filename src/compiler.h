#ifndef COMPILER_H
#define COMPILER_H

#include "scanner.h"
#include "memory.h"

namespace Oevyli {

class Compiler {
public:
  Compiler(const char* source): scanner(source), had_error(false), panic(false) {}
  ~Compiler() {}
  
  // Compiler fill the instructions buffer with relevent instructions
  bool compile(DMem<uint8_t>& instructions);

private:
  void advance();
  void consume(TokenType type, const char* message);
  void expression();

  // If scanner throws error tokens, inform the user
  void error_at_current(const char* message);
  // Inform about the error token the compiler just consumed
  void error(const char* message);
  void error_at(Token& token, const char* message);

private:
  Token previous, current;
  Scanner scanner;

  bool had_error; // If error occured during compilation
  bool panic;     // To avoid eror cascades
};

} // namespace Oevyli

#endif
