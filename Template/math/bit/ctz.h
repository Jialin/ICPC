#pragma once

#include <limits>

using namespace std;

namespace math {

template<typename T>
inline int ctz(T n) {
  if (!n) {
    return numeric_limits<T>::digits + numeric_limits<T>::is_signed;
  }
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshift-count-overflow"
  for (int res = 0; n; res += 32, n >>= 32) {
#pragma clang diagnostic pop
    uint32_t part = static_cast<uint32_t>(n & 0xFFFFFFFFU);
    if (part) {
      return res + __builtin_ctz(part);
    }
  }
  return -1;
}

} // namespace math
