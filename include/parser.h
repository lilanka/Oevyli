#ifndef OEVYLI_PARSER_H
#define OEVYLI_PARSER_H

#include <string>

#include "scanner.h"

namespace oevyli {

// data structure for parse tree
// it stores the node and it's siblings
struct Tree {
  Token data;
  Tree* child;
  Tree* sibling;
};

// parse message for compiler
enum class ParseMessage {
  PARSING_ERROR,
  MEMORY_ERROR,
  TREE_OK
};

class Parser {
public:
  Parser() {};
  Tree generate_parse_tree(const Token& token);

private:
  // create a tree (or a sub tree)
  Tree create_tree(const Token& token, Tree* child, Tree* sibling) const;

  // base function for parser checking
  // the token should match with the type and char_stream
  ParseMessage token_parse_base(const Token& token, Tree* tree, TokenType type , const char* character_stream);

  // get character from TokenType
  std::string token_to_character(const TokenType& type) const;

  // create character from token.
  // in the token implementation, a pointer to start of the lexeme and
  // lexeme length are stored
  std::string lexeme_from_token(const Token& token) const;
};

} // namespace oevyli

#endif