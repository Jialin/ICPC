#pragma once

#include <functional>

#include "math/prime/miller_rabin.h"
#include "math/prime/rho64.h"

using namespace std;

namespace math {

namespace {

inline bool divisorIterator64Dfs_(
    uint64_t x,
    uint64_t remN,
    uint64_t n,
    const std::function<bool(uint64_t)>& processor) {
  if (remN == 1) {
    uint64_t y = n / x;
    if (!processor(x)) {
      return false;
    }
    if (x < y) {
      if (!processor(y)) {
        return false;
      }
    }
    return true;
  }
  uint64_t p, nxtRemN;
  int cnt;
  if (millerRabin(remN)) {
    p = remN;
    cnt = 1;
    nxtRemN = 1;
  } else {
    p = remN;
    do {
      p = rho64(p, false);
    } while (p == n || !millerRabin(p));
    for (cnt = 1, nxtRemN = remN / p; !(nxtRemN % p); ++cnt, nxtRemN /= p) {}
  }
  if (!divisorIterator64Dfs_(x, nxtRemN, n, processor)) {
    return false;
  }
  for (int i = cnt; i > 0; --i) {
    x *= p;
    if (x > n / x) {
      break;
    }
    if (!divisorIterator64Dfs_(x, nxtRemN, n, processor)) {
      return false;
    }
  }
  return true;
}

} // namespace

inline void
divisorIterator64(uint64_t n, const std::function<bool(uint64_t)>& processor) {
  divisorIterator64Dfs_(1, n, n, processor);
}

} // namespace math
