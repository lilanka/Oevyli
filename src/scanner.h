#ifndef SCANNER_H
#define SCANNER_H

#include "common.h"

namespace Oevyli {

namespace Constants {

const int keyword_min_length = 4;
const int keyword_max_length = 5;

} // namespace Constants

enum class TokenType {
  // Single character tokens
  T_MINUS, T_PLUS, T_SLASH, T_STAR, 
  // One or two character tokens
  T_EQUAL, T_EQUAL_EQUAL, T_GREATER, T_GREATER_EQUAL,
  T_LESS, T_LESS_EQUAL, T_BANG, T_BANG_EQUAL,
  // Literals
  T_IDENTIFIER, T_STRING, T_NUMBER,
  // Keywords
  T_PRINT, T_TRUE, T_FALSE,  // We don't implement anything, untill we need it

  T_ERROR, T_EOF
};

struct Token {
  TokenType type;
  const char* start;
  int length;         // Length of the token string 
  size_t line;        // The line number of the token in the source file
};

// Information of the perticular token. Example variable x = x + x
//                                              ^     ^
//                                              start current
// When it comes to string, we don't store strings, just store pointer to
// the first character of the string, and length of the string.
class Scanner {
public:
  Scanner(const char* source): start(source), current(source) {}

  // When compiler ask for a new token, this generate new one.
  Token tokanize();

private:
  // General function to create a token
  Token create_token(const TokenType type) const;
  Token error_token(const char* message) const;
  // Determine of current is at the end of the file
  bool is_at_end() const;
  // Consumes current character and returs it
  char consume();
  // Gives current without consuming it 
  char next_char() const;
  // Gives char next to current without consuming it 
  char next_next_char() const;
  // If given character c matches current character, it consumes it and return true
  // Otherwise nothing happens
  bool is_it(char c);
  bool is_in_range(char c, char lower, char higher) const;
  void skip_whitespaces();

  // Handle string and number literals
  Token string();
  Token number();

  // Determine identifier and keyword tokens
  Token identifier_or_keyword();
  TokenType identifier_type() const;

private:
  const char* start;      // Start of the current token being scanned
  const char* current;    // Current character being scanned 
  size_t line = 1;        // Same as line in token, but use as current line being scanned
};

} // namespace Oevyli

#endif
