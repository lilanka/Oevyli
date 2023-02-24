#ifndef OEVYLI_SCANNER_H
#define OEVYLI_SCANNER_H

#include <cstddef>

namespace oevyli {

namespace oevyli_constants {
  const int keyword_min_length = 2;
  const int keyword_max_length = 7;
}

enum class TokenType {
  // keywords
  TSTRING, TI8, TI16, TI32, TI64, TF32, TF64, TTENSOR,
  TWHILE, TFOR, TIF, TELSE, TFN, TIS, TNOT, TPRINT,
  TMAIN, TRETURN,

  // single character
  TLPAREN, TRPAREN, TCOMMA, TPLUS,
  TMINUS, TSTAR, TSLASH,
  // double character
  TEQ, TEQ_EQ, TBANG, TBANG_EQ, TLESS, TLESS_EQ, TGREATER, TGREATER_EQ,

  // others
  TEOF, TCOMMENT, TIDENTIFIER, TINVALID
};

struct Token {
  TokenType type;       // type of the token
  const char* start;    // begining of the token
  std::size_t length;   // length of the token string
  std::size_t line;     // line number the token is in
};

class Scanner {
public:
  Scanner(const char* source): start{source}, current{source}, line{0} {}
  Token tokenize();

private:
  Token create_token(const TokenType type) const;
  Token identifier_or_keyword();
  Token comment();
  Token invalid_token() const;
  char current_character() const;
  char next_character() const;
  // advance current pointer by one
  char advance();
  void skip_whitespaces();
  bool is_at_end() const;
  bool in_range(const char c, const char lower, const char upper) const;
  // check if whether next character is 'c'
  bool is_character(const char c) const;

private:
  const char* start;
  const char* current;
  std::size_t line;
};

} // namespace oevyli

#endif