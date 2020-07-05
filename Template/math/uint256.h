#pragma once

namespace math {

class uint256 {
  static inline __uint128_t low_(__uint128_t x) {
    return static_cast<uint64_t>(x);
  }

  static inline __uint128_t high_(__uint128_t x) {
    return x >> 64;
  }

public:
  static inline uint256 mul(__uint128_t x, __uint128_t y) {
    __uint128_t lowX = low_(x), highX = high_(x), lowY = low_(y),
                highY = high_(y);
    __uint128_t t1 = lowX * lowY, t2 = highX * lowY + highY * lowX + high_(t1);
    return {highX * highY + high_(t2), (t2 << 64) + low_(t1)};
  }

  static inline __uint128_t mulHigh(__uint128_t x, __uint128_t y) {
    __uint128_t lowX = low_(x), highX = high_(x), lowY = low_(y),
                highY = high_(y);
    return highX * highY +
           high_(highX * lowY + highY * lowX + high_(lowX * lowY));
  }

  __uint128_t high, low;
};

} // namespace math
