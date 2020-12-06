#pragma once

namespace math {

inline int ctz128(__uint128_t n) {
  if (!n) {
    return 128;
  }
  if (!static_cast<uint64_t>(n)) {
    return __builtin_ctzll(static_cast<uint64_t>(n >> 64)) + 64;
  } else {
    return __builtin_ctzll(static_cast<uint64_t>(n));
  }
}

} // namespace math
