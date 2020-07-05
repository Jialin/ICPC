#pragma once

#include "math/uint256.h"

namespace math {

class MontgomeryMul {
public:
  inline MontgomeryMul() {}

  inline MontgomeryMul(__uint128_t oddMod_) {
    init(oddMod_);
  }

  inline void init(__uint128_t oddMod_) {
    mod = oddMod_;
    inv_ = 1;
    for (int i = 0; i < 7; ++i) {
      inv_ *= 2 - mod * inv_;
    }
    r2_ = -mod % mod;
    for (int i = 0; i < 4; ++i) {
      r2_ <<= 1;
      if (r2_ >= mod) {
        r2_ -= mod;
      }
    }
    for (int i = 0; i < 5; ++i) {
      r2_ = mul(r2_, r2_);
    }
    one = convert(1);
  }

  inline __uint128_t convert(__uint128_t x) const {
    return mul(x, r2_);
  }

  inline __uint128_t revert(__uint128_t low, __uint128_t high = 0) const {
    __uint128_t a = uint256::mulHigh(low * inv_, mod);
    return high >= a ? high - a : mod - (a - high);
  }

  inline __uint128_t mul(__uint128_t x, __uint128_t y) const {
    auto xy = uint256::mul(x, y);
    return revert(xy.low, xy.high);
  }

  __uint128_t mod, one;

private:
  __uint128_t inv_, r2_;
};

} // namespace math
