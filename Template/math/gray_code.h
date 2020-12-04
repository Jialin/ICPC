#pragma once

namespace math {

// Computes the n-th gray code
template<typename V = int>
inline V grayCode(V n) {
  return n ^ (n >> 1);
}

} // namespace math