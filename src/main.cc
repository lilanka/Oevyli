#include <iostream>
#include <algorithm>
#include <cstring>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "compile.h"

using namespace oevyli;

static const char* read_file(const char* fname) {
  auto fd = open(fname, O_RDONLY);
  if (fd < 0) perror("mmap() open error");

  struct stat sb;
  if (fstat(fd, &sb) == -1)
    perror("fstat error");
  size_t length = sb.st_size;
  const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
  if (addr == MAP_FAILED) perror("mmap failed");
  return addr;
}

static void compile(const char* source_path) {
  const char* source_code = read_file(source_path);

  Compile compile(source_code);
}

int main(int argc, const char* argv[]) {
  if (argc == 2) {
    compile(argv[1]);
  } else {
    std::cout << "Invalid path for .ovli file" << std::endl;
    exit(64);
  }
  return 0;
}