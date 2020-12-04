#pragma once

namespace math {

template<typename V = int>
inline V invGrayCode(V v) {
  V n = 0;
  for (; v; v >>= 1) {
    n ^= v;
  }
  return n;
}

} // namespace math