#pragma once

#include <cstdint>

namespace math {

template<typename V = int32_t>
inline V slightFixMod(V v, const V& mod) {
  if (v < 0) {
    v += mod;
  }
  if (v >= mod) {
    v -= mod;
  }
  return v;
}

} // namespace math
