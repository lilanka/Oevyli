#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <cstdlib>

namespace Oevyli {

// I chose factor as 1.5 (see https://github.com/facebook/folly/blob/main/folly/docs/FBVector.md)
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 1.5)

#define GROW_ARRAY(type, pointer, old_count, new_count) \
  (type*)reallocate(pointer, sizeof(type) * (old_count), sizeof(type) * (new_count))

#define FREE_ARRAY(type, pointer, old_count) \
  reallocate(pointer, sizeof(type) * (old_count), 0) 

// This is where memory allocation happens
void* reallocate(void* pointer, size_t old_size, size_t new_size);

template <class T>
class DMem {
public:
  int count, capacity;
  T* values;

  DMem(): count(0), capacity(0), values(nullptr) {}
  ~DMem() {}

  // Wrtie on the buffer 
  void write(T value) {
    if (capacity < count + 1) {
      int old_capacity = capacity;
      capacity = GROW_CAPACITY(old_capacity);
      values = GROW_ARRAY(T, values, old_capacity, capacity);
    }
    values[count] = value;
    count++;
  }
	
  // Write on the buffer and get the index of the buffer which the value written in
  int write_and_get_index(T value) {
    write(value);
    return count - 1;
  }

	int size() { return count; }

	T item(int i) {
		if (i >= count) {
			std::cout << "Index out of range\n";
			exit(1);
		}
		return values[i];
	}

  // Free the buffer. Of course we can use disructor :)
  void free() {
    FREE_ARRAY(T, values, capacity);
    count = 0;
    capacity = 0;
    values = nullptr;
  }
};

} // namespace Oevyli

#endif
