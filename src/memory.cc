#include "memory.h"

namespace Oevyli {

void* reallocate(void* pointer, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    std::free(pointer);
    return nullptr;
  }
  void* result = realloc(pointer, new_size);
  if (result == nullptr) exit(1);
  return result;
}

} // namespace Oevyli
