#pragma once

#include <string>

#include "io/write_char_array.h"

using namespace std;

namespace io {

inline void writeString(const std::string& s) {
  writeCharArray(s.c_str());
}

} // namespace io
