#include "scanner.h"

namespace Oevyli {

Token Scanner::create_token(const TokenType type) const {
  Token token;
  token.start = start;
  token.type = type;
  token.line = line;
  token.length = (int)(current - start);
  return token;
}

Token Scanner::error_token(const char* message) const {
  Token token;
  token.start = message;
  token.type = TokenType::T_ERROR;
  token.line = line;
  token.length = 0;
  return token;
}

bool Scanner::is_at_end() const {
  return *current == '\0';
}

char Scanner::consume() {
  current++;
  return current[-1];
}

char Scanner::next_char() const {
  return *current;
}

char Scanner::next_next_char() const {
  if (is_at_end()) return '\0';
  return current[1];
}

bool Scanner::is_it(char c) {
  if (is_at_end()) return false;
  if (*current != c) return false;
  current++;
  return true;
}

void Scanner::skip_whitespaces() {
  while (true) {
    char c = next_char();
    switch (c) {
      case ' ':
      case '\r':
      case '\t': consume(); break;
      case '\n': line++; consume(); break;
      case ';': while (next_char() != '\n' && !is_at_end()) consume();
      default: return;
    }
  }
}

// TODO (Lilanka): 
//	* Check if there languages with multiline strings?
// 	* Add string interpolation
Token Scanner::string() {
  while (next_char() != '"' && !is_at_end()) {
    if (next_char() == '\n') line++;
    consume();
  }

  if (is_at_end()) return error_token("Unterminated string"); 

  consume();
  return create_token(TokenType::T_STRING);
}

Token Scanner::number() {
  if (is_in_range(next_char(), '0', '9')) consume();
  if (next_char() == '.' && is_in_range(next_next_char(), '0', '9')) {
    consume();
    while (is_in_range(next_char(), '0', '9')) consume();
  }
  return create_token(TokenType::T_NUMBER);
}

bool Scanner::is_in_range(char c, char lower, char higher) const {
  return c >= lower && c <= higher;  
}

TokenType Scanner::identifier_type() const {
  return TokenType::T_IDENTIFIER;
}

Token Scanner::identifier_or_keyword() {
  // Identifiers
  while (is_in_range(next_char(), 'a', 'z') || \
         is_in_range(next_char(), 'A', 'Z') || \
         is_in_range(next_char(), '0', '9') || \
         next_char() == '_') 
    consume();

  const int token_length = current - start;
  if (token_length < Constants::keyword_min_length || \
      token_length > Constants::keyword_max_length)
    return create_token(TokenType::T_IDENTIFIER);

#define KEYWORDS(KEYWORD_GROUP, KEYWORD)  \
  KEYWORD_GROUP('p')                      \
  KEYWORD("print", TokenType::T_PRINT)    \
  KEYWORD_GROUP('t')                      \
  KEYWORD("true", TokenType::T_TRUE)      \
  KEYWORD_GROUP('f')                      \
  KEYWORD("false", TokenType::T_FALSE)

  switch (start[0]) {
    default:
#define KEYWORD_GROUP_CASE(ch)            \
      break;                              \
    case ch:
#define KEYWORD(keyword, token_type) {                              \
  const int keyword_length = sizeof(keyword) - 1;                  	\
  if (token_length == keyword_length && start[1] == keyword[1] &&   \
      (keyword_length <= 2 || start[2] == keyword[2]) &&            \
      (keyword_length <= 3 || start[3] == keyword[3]) &&            \
      (keyword_length <= 4 || start[4] == keyword[4]))							\
    return create_token(token_type);                                \
  }
    KEYWORDS(KEYWORD_GROUP_CASE, KEYWORD)
  }
  return create_token(TokenType::T_IDENTIFIER);
#undef KEYWORDS
#undef KEYWORD
#undef KEYWORD_GROUP_CASE
}

Token Scanner::tokanize() {
  skip_whitespaces();
  start = current;

  if (is_at_end()) return create_token(TokenType::T_EOF);

  char c = consume();

  if (is_in_range(c, 'a', 'z') || is_in_range(c, 'A', 'Z') || c == '_') 
    return identifier_or_keyword();
  if (is_in_range(c, '0', '9')) return number();

  switch (c) {
    case '-': return create_token(TokenType::T_MINUS);
    case '+': return create_token(TokenType::T_PLUS);
    case '/': return create_token(TokenType::T_SLASH);
    case '*': return create_token(TokenType::T_STAR);
    case '!': return create_token(is_it('=') ? TokenType::T_BANG_EQUAL : TokenType::T_BANG);
    case '>': return create_token(is_it('=') ? TokenType::T_GREATER_EQUAL : TokenType::T_GREATER);
    case '<': return create_token(is_it('=') ? TokenType::T_LESS_EQUAL : TokenType::T_LESS);
    case '=': return create_token(is_it('=') ? TokenType::T_EQUAL_EQUAL : TokenType::T_EQUAL);
    case '"': return string();
  }
  return error_token("Unrecorgnized character");
}

} // namespace Oevyli
