#pragma once

namespace math {

inline uint32_t nextPow2_32(uint32_t v) {
  if (!v) {
    return 1;
  }
  uint32_t res = 1U << (31 - __builtin_clz(v));
  return res == v ? res : res << 1;
}

} // namespace math
