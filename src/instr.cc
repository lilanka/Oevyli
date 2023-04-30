#include "instr.h"
#include "memory.h"

namespace Oevyli {

void Instr::write(uint8_t byte) {
  if (capacity < count + 1) {
    int old_capacity = capacity;
    capacity = GROW_CAPACITY(old_capacity);
    code = GROW_ARRAY(uint8_t, code, old_capacity, capacity);
  }
  code[count] = byte;
  count++;
}

void Instr::free() {
  FREE_ARRAY(uint8_t, code, capacity);
  count = 0;
  capacity = 0;
  code = nullptr;
}

} // namespace Oevyli
