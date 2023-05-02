#ifndef COMPILER_H
#define COMPILER_H

#include "common.h"
#include "opcodes.h"
#include "scanner.h"
#include "memory.h"
#include "value.h"

namespace Oevyli {

// Parsing and Code generation happens here
class Compiler {
public:
  Compiler(const char* source, DArray<uint8_t>& instructions): 
    scanner(source), instructions(instructions), had_error(false), panic_mode(false) {};

  // Compilation starts here. It takes the source file as input
  // and do the compilation and running 
  bool compile();

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

  // Translate Tokens to bytecode
  // Write byte to the instruction buffer
  void write_byte(uint8_t byte);
  void write_byte(uint8_t byte1, uint8_t byte2);

  // Parsing conversions
  // Compile number literals
  void number();

  void gen_constant(Value value);
  void make_constant(Value value);

private:
  DArray<uint8_t> instructions;
  Scanner scanner;
  Token previous;
  Token current;
  bool had_error;   // If there are errors in compilation stage
  bool panic_mode;  // To avoid error cascades
};

} // namespace Oevyli

#endif
