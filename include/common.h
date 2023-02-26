#ifndef OEVYLI_COMMON_H
#define OEVYLI_COMMON_H

#include <iostream>
#include <string>

namespace oevyli {

// inform the user
#define OEVYLI_MESSAGE(message)                     \
  std::cout << "Oevyli " << message << std::endl;

} // namespace oevyli

#endif
