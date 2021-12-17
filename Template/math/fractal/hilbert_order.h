#pragma once

#include "common/macros.h"

using namespace std;

namespace math {

inline int64_t hilbertOrder(int bit, int x, int y) {
  int64_t res = 0;
  for (int n = 1 << bit, s = n >> 1; s; s >>= 1) {
    int rotateX = (x & s) ? 1 : 0;
    int rotateY = (y & s) ? 1 : 0;
    res += CAST<int64_t>(s) * s * ((rotateX) ^ (rotateY * 3));
    if (rotateX) {
      continue;
    }
    if (rotateY) {
      x = n - 1 - x;
      y = n - 1 - y;
    }
    swap(x, y);
  }
  return res;
}

} // namespace math
