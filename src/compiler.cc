#include <iostream>

#include "compiler.h"

namespace Oevyli {

void Compiler::error_at(Token& token, const char* message) {
  // We don't want make user more panic 
  if (panic) return;
  panic = true; 
  std::cout << "[line " << token.line << "] Error";
  
  if (token.type == TokenType::T_EOF) {
    std::cout << " at end";
  } else if (token.type == TokenType::T_ERROR) {
  } else {
    std::cout << " at " << token.length << ", " << token.start;
  }
  std::cout << ": " << message << std::endl;
  had_error = true;
}

void Compiler::error_at_current(const char* message) {
  error_at(current, message);
}

void Compiler::error(const char* message) {
  error_at(previous, message);
}

void Compiler::consume(TokenType type, const char* message) {
  if (current.type == type) {
    advance();
    return;
  }
  error_at_current(message);
}

void Compiler::expression() {}

void Compiler::advance() {
  previous = current;

  while (true) {
    current = scanner.tokanize();

    if (current.type != TokenType::T_ERROR) 
      break;
    error_at_current(current.start);
  }
}

bool Compiler::compile(DMem<uint8_t>& instructions) {
  advance();
  expression();
  consume(TokenType::T_EOF, "Expect end of expression");
  return !had_error; 
}

} // namespace Oevyli
