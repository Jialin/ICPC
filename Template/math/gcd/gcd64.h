#pragma once

#include <algorithm>

using namespace std;

namespace math {

inline uint64_t gcd64(uint64_t a, uint64_t b) {
  if (!a || !b) {
    return a | b;
  }
  auto shift = __builtin_ctzll(a | b);
  a >>= __builtin_ctzll(a);
  do {
    b >>= __builtin_ctzll(b);
    if (a > b) {
      swap(a, b);
    }
    b -= a;
  } while (b);
  return a << shift;
}

} // namespace math
