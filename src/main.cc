#include <iostream>

#include "vm.h"

using namespace Oevyli;

static void repl() {}

// TODO (Lilanka): Find a efficient way to read the source file 
static const char* read_file(const char* fname) {
  const char* source = "variable x = x * x";
  return source; 
}

static void compile(const char* fname) {
  const char* source = read_file(fname);
  VM vm;
  InterpretResult result = vm.interpret(source);
}

int main(int argc, const char* argv[]) {
#define DEBUG_MODE
#ifdef DEBUG_MODE
  compile("../test1.oli");
#else
  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    compile(argv[1]);
  } else {
    std::cout << "Error: Invalid Path" << std::endl;
  }
#endif
  return 0;
}
