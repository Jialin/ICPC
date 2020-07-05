#pragma once

namespace math {

inline int ctz128(__uint128_t n) {
  if (!static_cast<uint64_t>(n)) {
    return !(n >> 64) ? 128 : __builtin_ctzll(n >> 64) + 64;
  } else {
    return __builtin_ctzll(n);
  }
}

} // namespace math
