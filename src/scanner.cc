#include <iostream>

#include "scanner.h"

namespace oevyli {

Token Scanner::tokenize() {
  std::cout << start+1;

  Token token = create_token(TokenType::TEOF, 0);
  return token;
}

Token Scanner::create_token(const TokenType type, const std::size_t line) const {
  Token token;
  token.type = type;
  token.line = line;
  return token;
}

} // namespace oevyli