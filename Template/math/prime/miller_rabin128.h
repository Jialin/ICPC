#pragma once

#include "math/ctz128.h"
#include "math/mod/exp128.h"
#include "math/montgomery_mul.h"

using namespace std;

namespace math {

namespace {

const __uint128_t PRIMES[25] = {2,  3,  5,  7,  11, 13, 17, 19, 23,
                                29, 31, 37, 41, 43, 47, 53, 59, 61,
                                67, 71, 73, 79, 83, 89, 97};

inline bool checkComposite128(
    const MontgomeryMul& mont, __uint128_t a, __uint128_t d, int s) {
  __uint128_t x = exp128(mont, mont.convert(a), d);
  if (x == mont.one || x == mont.mod - mont.one) {
    return false;
  }
  for (int i = 1; i < s; ++i) {
    x = mont.mul(x, x);
    if (x == mont.mod - mont.one) {
      return false;
    }
  }
  return true;
}

} // namespace

inline bool
millerRabin128(__uint128_t n, MontgomeryMul& mont, bool initMont = true) {
  if (n < 2) {
    return false;
  }
  for (int i = 0; i < 25; ++i) {
    if (n == PRIMES[i]) {
      return true;
    }
    if (!(n % PRIMES[i])) {
      return false;
    }
  }
  __uint128_t n1 = n - 1;
  int ctz = ctz128(n1);
  n1 >>= ctz;
  if (initMont) {
    mont.init(n);
  }
  for (int i = 0; i < 25; ++i) {
    if (checkComposite128(mont, PRIMES[i], n1, ctz)) {
      return false;
    }
  }
  return true;
}

} // namespace math
