// ------------------------------------
// Copyright (C) 2023 Lilanka Pathirage
// ------------------------------------

#include "scanner.h"

namespace Oevyli {

Token Scanner::create_token(const TokenType type) {
  Token token;
  token.type = type;
  token.line = line;
  return token;
}

Token Scanner::tokanize() {
  return Token(TokenType::T_EOF);
}

} // namespace Oevyli
