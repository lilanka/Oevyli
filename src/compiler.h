// ------------------------------------
// Copyright (C) 2023 Lilanka Pathirage
// ------------------------------------

#ifndef COMPILER_H
#define COMPILER_H

#include "common.h"

namespace Oevyli {

class Compiler {
public:
  Compiler() {};

  // Compilation starts here. It takes the source file as input
  // and do the compilation and running 
  void compile(const char* source);
};

} // namespace Oevyli

#endif
