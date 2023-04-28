// ------------------------------------
// Copyright (C) 2023 Lilanka Pathirage
// ------------------------------------

#ifndef SCANNER_H
#define SCANNER_H

#include "common.h"

namespace Oevyli {

enum class TokenType {
  T_RETURN,
  T_EOF
};

// Information of the perticular token
//  "variable x = x + x"
//   ^     ^
// start  current 
struct Token {
  TokenType type;
  size_t line;      // The line number of the token in the source file
};

class Scanner {
public:
  Scanner(const char* source) : start(source), current(source) {}

  // When compiler ask for a new token, this generate new one.
  Token tokanize();

private:
  // General function to create a token
  Token create_token(const TokenType type);

private:
  const char* start;      // Start of the current token being scanned
  const char* current;    // Current character being scanned 
  size_t line = 1;   // Same as line in token, but use as current line being scanned
};

} // namespace Oevyli

#endif
