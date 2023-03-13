// Memory interface

#ifndef MEMORY_H
#define MEMORY_H

#include "comm.h"

// New capacity scales based on current capacity c
// We grow by factor of 2. We have to profile this
// in real world case and decide optimal factor
#define oli_grow_capacity(c) ((c) < 8 ? 8 : (c) * 2)

// Grow the vector for given size
#define oli_grow_vector(type, pointer, old_count, new_count) \
  (type*)reallocate(pointer, sizeof(type) * (old_count), sizeof(type) * (new_count))

#define oli_alignment 8
#define oli_align(size) (((size) + (oli_alignment - 1)) & ~(oli_alignment - 1))

// Header size
#define oli_size_t_size (oli_align(sizeof(size_t)))

// Dynamic memory management for oevlie
// Memory allocation, freeing, and size changing of existing allocation
// happens in a single function
void* reallocate(void* pointer, size_t old_size, size_t new_size);



// Custom malloc and free implementations
// Don't use standard malloc, or free in oevyli
void *oli_malloc(size_t size);

#endif