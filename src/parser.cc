#include <iostream>

#include "parser.h"
#include "common.h"
#include "debug.h"

namespace oevyli {

Tree Parser::create_tree(const Token& token, Tree* child, Tree* sibling) const {
  Tree tree;
  tree.data = token;
  tree.child = child;
  tree.sibling = sibling;
  return tree;
}

std::string Parser::token_to_character(const TokenType& type) const {
  switch (type) {
    case TokenType::TFN: return "fn";
    case TokenType::TLPAREN: return "(";
    case TokenType::TRPAREN: return ")";
    case TokenType::TMAIN: return "main()";
    case TokenType::TRETURN: return "return";
    case TokenType::TPLUS: return "+";
    case TokenType::TCOMMA: return "-";
    case TokenType::TEQ: return "=";
    case TokenType::TPRINT: return "print";
    default: return "";
  }
}

std::string Parser::lexeme_from_token(const Token& token) const {
  std::string lexeme = "";
  for (int i = 0; i < token.length; ++i)
    lexeme += token.start[i];
  return lexeme;
}

ParseMessage Parser::token_parse_base(const Token& token, Tree* tree, TokenType type, const char* character_stream) {
  Token current = token;
  if (current.type != type) {
    std::cout << "Expecting " << token_to_character(type) << ", but found " << token_to_character(token.type) << std::endl;
    return ParseMessage::PARSING_ERROR;
  }

  std::string lexeme = lexeme_from_token(token);
  if (character_stream != nullptr && lexeme == character_stream) {
    std::cout << "Expecting " << character_stream << ", but found " << lexeme << std::endl;
    return ParseMessage::PARSING_ERROR;
  }

  return ParseMessage::TREE_OK;
}

Tree Parser::generate_parse_tree(const Token& token) {
  Tree tree = create_tree(token, nullptr, nullptr);
  return tree;
}

} // namespace oevyli