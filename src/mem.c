// Memory interface

#include <stdlib.h>

#include "comm.h"
#include "mem.h"

// I followed https://moss.cs.iit.edu/cs351/slides/slides-malloc.pdf
// for malloc implementation

// Block structure
// +-------------------------------------+
// | header | payload + padding | footer |
// +-------------------------------------+

static void *coalesce(size_t *bp) {
  size_t *next = (char *)bp + (*bp & ~1L);
  size_t *prev = (char *)bp - (*(size_t *)((char *)bp - oli_size_t_size) & ~1L);
  int next_alloc = *next & 1;
  int prev_alloc = *prev & 1;

  if (prev_alloc && next_alloc) {
    return bp;
  } else if (!prev_alloc && next_alloc) {
    *prev += *bp; // header
    *(size_t *)((char *)bp + *bp - oli_size_t_size) = *prev; // footer
    return prev;
  } else if (prev_alloc && !next_alloc) {
    // todo
  }
}

// Search heap for free blocks less than required size
static void *find_fit(size_t size) {
  size_t *header = heap_start(), *next;
  while (header < heap_end()) {
    if (!(*header & 1)) {
      if (*header >= size) return header;
      next = (char *)header + *header;
      // Merge with next block if available and free
      if (next < heap_end() && !(*next & 1)) {
        *header += *next;
        continue;
      }
    }
    header = (char *)header + (*header & ~1L);
  }
  return NULL;
}

void *oli_malloc(size_t size) {
  size_t block_size = oli_align(size + oli_size_t_size);
  size_t *header = find_fit(block_size);
  if (header && block_size < *header)
    *(size_t *)((char *)header + block_size) = *header - block_size;
  else
    *header = sbrk(block_size);
  *header = block_size | 1;
  return (char *)header + 8;
}

void oli_free(void *pointer) {
  size_t *header = (char *)pointer - oli_size_t_size, *next;
  // Unmark allocated bit
  *header = *header & ~1L;

  // Coalesce if possible
  next = (char *)header + *header;
  if (next <= heap_end() && !(*next & 1)) {
    *header += *next;
  }
}

void* reallocate(void* pointer, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free_mem(pointer);
    return NULL;
  }
  void* result = realloc_mem(pointer, new_size);
  return result;
}
