#include "parser.h"
#include "common.h"
#include "debug.h"

namespace oevyli {

Tree Parser::create_tree(const Token token, Tree* child, Tree* sibling) {
  Tree tree;
  tree.data = token;
  tree.child = child;
  tree.sibling = sibling;
  return tree;
}

} // namespace oevyli