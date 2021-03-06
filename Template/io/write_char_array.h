#pragma once

#include "io/write_char.h"

namespace io {

inline void writeCharArray(const char* s) {
  for (size_t i = 0; s[i]; ++i) {
    writeChar(s[i]);
  }
}

} // namespace io
