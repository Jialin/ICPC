#pragma once

#include <cstdint>

namespace math {

template<typename V = int>
inline void slightFixModInline(V& v, const V& mod) {
  if (v < 0) {
    v += mod;
  }
  if (v >= mod) {
    v -= mod;
  }
}

} // namespace math
