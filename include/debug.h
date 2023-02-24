#ifndef OEVYLI_DEBUG_H
#define OEVYLI_DEBUG_H

#include <iostream>
#include <string>

#include "scanner.h"

namespace oevyli {

#define DEBUG_MESSAGE(message) {      \
  std::cout << message << std::endl;  \
}

static void debug_token(const Token& token) {
  switch (token.type) {
    case TokenType::TCOMMENT: DEBUG_MESSAGE("TCOMMENT"); break;
    case TokenType::TFN: DEBUG_MESSAGE("TFN"); break;
    case TokenType::TIDENTIFIER: DEBUG_MESSAGE("TIDENTIFIER"); break;
    case TokenType::TLPAREN: DEBUG_MESSAGE("TLPAREN"); break;
    case TokenType::TRPAREN: DEBUG_MESSAGE("TRPAREN"); break;
    case TokenType::TMAIN: DEBUG_MESSAGE("TMAIN"); break;
    case TokenType::TRETURN: DEBUG_MESSAGE("TRETURN"); break;
    case TokenType::TPLUS: DEBUG_MESSAGE("TPLUS"); break;
    case TokenType::TCOMMA: DEBUG_MESSAGE("TCOMMA"); break;
    case TokenType::TEQ: DEBUG_MESSAGE("TEQ"); break;
    case TokenType::TPRINT: DEBUG_MESSAGE("TPRINT"); break;
    default: DEBUG_MESSAGE("TINVALID"); break;
  }
}

} // namespace oevyli

#endif