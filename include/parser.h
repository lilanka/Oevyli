#ifndef OEVYLI_PARSER_H
#define OEVYLI_PARSER_H

#include "scanner.h"

namespace oevyli {

// data structure for parse tree
// it stores the node and it's siblings
struct Tree {
  Token data;
  Tree* child;
  Tree* sibling;
};

class Parser {
public:
  Parser(const TokenList& token_list): token_list{token_list} {}
  Tree generate_parse_tree();

private:
  // create a tree (or a sub tree)
  Tree create_tree(const Token token, Tree* child, Tree* sibling);

private:
  TokenList token_list;
};

} // namespace oevyli

#endif