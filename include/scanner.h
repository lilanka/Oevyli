#ifndef OEVYLI_SCANNER_H
#define OEVYLI_SCANNER_H

#include <cstddef>

namespace oevyli {

enum class TokenType {
  // Keywords
  TSTRING, TI8, TI16, TI32, TI64, TF32, TF64, TTENSOR,
  TWHILE, TFOR, TIF, TELSE, TFN, TIS, TNOT, TPRINT,
  // Single character
  TLPAREN, TRPAREN, TCOMMA, TPLUS,
  TMINUS, TSTAR, TSLASH,
  // Double character
  TEQ, TEQ_EQ, TBANG, TBANG_EQ, TLESS, TLESS_EQ, TGREATER, TGREATER_EQ,

  // Others
  TEOF
};

struct Token {
  TokenType type;    // Type of the token
  std::size_t line;  // Line number the token is in
};

class Scanner {
public:
  Scanner(const char* source): start(source), current(source) {}
  Token tokenize();

private:
  Token create_token(const TokenType type, const std::size_t line) const;

private:
  const char* start;
  const char* current;
};

} // namespace oevyli

#endif