#include <iostream>

#include "scanner.h"
#include "debug.h"

namespace oevyli {

Scanner::~Scanner() {}

char Scanner::current_character() const {
  return *current;
}

char Scanner::advance() {
  current++;
  return current[-1];
}

char Scanner::next_character() const {
  return *current;
}

void Scanner::skip_whitespaces() {
  while (true) {
    switch (next_character()) {
      case ' ':
      case '\r':
      case '\t': advance(); break;
      case '\n': advance(); line++; break;
      default: return;
    }
  }
}

bool Scanner::is_at_end() const {
  return *current == '\0';
}

bool Scanner::in_range(const char c, const char lower, const char upper) const {
  return c >= lower && c <= upper;
}

bool Scanner::is_character(const char c) const {
  return *(current + 1) == c;
}

// followed a cool method to identify keyword by V8 JS Engine
Token Scanner::identifier_or_keyword() {
  while (in_range(next_character(), 'a', 'z') ||  \
          in_range(next_character(), 'A', 'Z') || \
          in_range(next_character(), '1', '9') || \
          next_character() == '_')
    advance();

  const auto token_length = current - start;
  if (token_length < oevyli_constants::keyword_min_length || \
      token_length > oevyli_constants::keyword_max_length)
    return create_token(TokenType::TIDENTIFIER);

// todo: add other keywords
#define KEYWORDS(KEYWORD_GROUP, KEYWORD)  \
  KEYWORD_GROUP('e')                      \
  KEYWORD("ELSE", TokenType::TELSE)       \
  KEYWORD_GROUP('p')                      \
  KEYWORD("print", TokenType::TPRINT)     \
  KEYWORD_GROUP('f')                      \
  KEYWORD("f32", TokenType::TF32)         \
  KEYWORD("fn", TokenType::TFN)           \
  KEYWORD_GROUP('m')                      \
  KEYWORD("main", TokenType::TMAIN)       \
  KEYWORD_GROUP('r')                      \
  KEYWORD("return", TokenType::TRETURN)

  switch (start[0]) {
    default:
#define KEYWORD_GROUP_CASE(ch)            \
      break;                              \
    case ch:
#define KEYWORD(keyword, token_type) {                              \
  const auto keyword_length = sizeof(keyword) - 1;                  \
  if (token_length == keyword_length && start[1] == keyword[1] &&   \
      (keyword_length <= 2 || start[2] == keyword[2]) &&            \
      (keyword_length <= 3 || start[3] == keyword[3]) &&            \
      (keyword_length <= 4 || start[4] == keyword[4]) &&            \
      (keyword_length <= 5 || start[5] == keyword[5]) &&            \
      (keyword_length <= 6 || start[6] == keyword[6]))              \
    return create_token(token_type);                                \
  }
    KEYWORDS(KEYWORD_GROUP_CASE, KEYWORD)
  }
  return create_token(TokenType::TIDENTIFIER);
#undef KEYWORDS
#undef KEYWORD
#undef KEYWORD_GROUP_CASE
}

Token Scanner::create_token(const TokenType type) const {
  Token token;
  token.type = type;
  token.line = line;
  token.start = start;
  token.length = current - start;
  return token;
}

Token Scanner::invalid_token() const {
  Token token;
  token.type = TokenType::TINVALID;
  token.start = nullptr;
  return token;
}

Token Scanner::comment() {
  while (next_character() != '\n' && !is_at_end())
    advance();
  return create_token(TokenType::TCOMMENT);
}

Token Scanner::tokenize() {
  skip_whitespaces();
  start = current;

  if (is_at_end())
    return create_token(TokenType::TEOF);

  auto c = advance();

  if (in_range(c, 'a', 'z') || in_range(c, 'A', 'Z') || c == '_')
    return identifier_or_keyword();

  switch (c) {
    case '(': return create_token(TokenType::TLPAREN);
    case ')': return create_token(TokenType::TRPAREN);
    case ',': return create_token(TokenType::TCOMMA);
    case '+': return create_token(TokenType::TPLUS);
    case '-': return create_token(TokenType::TMINUS);
    case '*': return create_token(TokenType::TSTAR);
    case '/': return create_token(TokenType::TSLASH);

    // todo: add multiline commenting feature
    case '#': return comment();
    case '!': return create_token(is_character('=') ? TokenType::TBANG_EQ : TokenType::TBANG);
    case '=': return create_token(is_character('=') ? TokenType::TEQ_EQ : TokenType::TEQ);
    case '<': return create_token(is_character('=') ? TokenType::TLESS_EQ : TokenType::TLESS);
    case '>': return create_token(is_character('=') ? TokenType::TGREATER_EQ : TokenType::TGREATER);
  }
  return invalid_token();
}

} // namespace oevyli