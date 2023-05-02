#include <iostream>

#include "compiler.h"
#include "debug.h"

namespace Oevyli {

void Compiler::make_constant(Value value) {}

void Compiler::gen_constant(Value value) {
  //write_byte(OP_CONSTANT, make_constant(value));
}

void Compiler::number() {
  double value = strtod(previous.start, nullptr);
  gen_constant(value);
}

void Compiler::write_byte(uint8_t byte) {
  instructions.write(byte);
}

void Compiler::write_byte(uint8_t byte1, uint8_t byte2) {
  instructions.write(byte1);
  instructions.write(byte2);
}

void Compiler::consume(TokenType type, const char* message) {
  if (current.type == type) {
    advance();
    return;
  }
  error_at_current(message);
}

void Compiler::error_at(Token& token, const char* message) {
  // If we're in panic, we don't throw more errors
  if (panic_mode) return;
  panic_mode = true;
  std::cout << "Line " << token.line << " Error";

  if (token.type == TokenType::T_EOF) {
    std::cout << " at end"; 
  } else if (token.type == TokenType::T_ERROR) {
  } else {
    std::cout << " at " << token.start;
  }

  std::cout << " " << message << std::endl;
  had_error = true;
}

void Compiler::error(const char* message) {
  error_at(previous, message);
}

void Compiler::error_at_current(const char* message) {
  error_at(current, message);
}

void Compiler::advance() {
  previous = current;
  
  while (true) {
    current = scanner.tokanize();
    if (current.type != TokenType::T_ERROR) break;

    // Scanner throws error tokens
    error_at_current(current.start);
  }
}

void Compiler::expression() {}

bool Compiler::compile() {
  advance();
  expression();
  consume(TokenType::T_EOF, "Expect end of expression");
  instructions.write(OP_RETURN);
  return !had_error;

  /* for testing 
  int line = -1;
  bool scanning = true;
  while (scanning) {
    Token token = scanner.tokanize();
    if (token.line != line) {
      line = token.line;
    } else {
      std::cout << "  | ";
    }
    std::cout << static_cast<int>(token.type) << " " << token.length << " " << std::endl;

    if (token.type == TokenType::T_ERROR) {
      //scanning = false;
      std::cout << "Unrecorgnized token" << std::endl;
    } else if (token.type == TokenType::T_EOF) {
      scanning = false;
      std::cout << "Scanning finished" << std::endl;
    }
  }
  // Successfully compiled 
  return true;
  */
}

} // namespace Oevyli
