#ifndef MEMORY_H
#define MEMORY_H

#include <cstdlib>

#include "common.h"

namespace Oevyli {

// I chose factor as 1.5 (see https://github.com/facebook/folly/blob/main/folly/docs/FBVector.md)
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 1.5)

#define GROW_ARRAY(type, pointer, old_count, new_count) \
  (type*)reallocate(pointer, sizeof(type) * (old_count), sizeof(type) * (new_count))

#define FREE_ARRAY(type, pointer, old_count) \
  reallocate(pointer, sizeof(type) * (old_count), 0) 

void* reallocate(void* pointer, size_t old_size, size_t new_size);

} // namespace Oevyli

#endif
