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

template <typename T>
class DArray {
public:
  int count;
  int capacity;
  T* values;

  DArray(): count(0), capacity(0), values(nullptr) {}
  ~DArray() {}

  // Wrtie on the array
  void write(T value) {
    if (capacity < count + 1) {
      int old_capacity = capacity;
      capacity = GROW_CAPACITY(old_capacity);
      values = GROW_ARRAY(T, values, old_capacity, capacity);
    }
    values[count] = value;
    count++;
  }

  void free() {
    FREE_ARRAY(T, values, capacity);
    count = 0;
    capacity = 0;
    values = nullptr;
  }

};

} // namespace Oevyli

#endif
