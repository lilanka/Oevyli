#ifndef OEVYLI_DEBUG_H
#define OEVYLI_DEBUG_H

#include <iostream>

namespace oevyli {

#define DEBUG_MESSAGE(message) {      \
  std::cout << message << std::endl;  \
}

} // namespace oevyli

#endif