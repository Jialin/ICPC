#pragma once

#include <functional>
#include <vector>

#include "debug/debug.h"

using namespace std;

namespace math {

namespace {

inline bool divisorIterator32Dfs_(
    int idx,
    const vector<int>& primes,
    uint32_t x,
    uint32_t remN,
    uint32_t n,
    const std::function<bool(uint32_t)>& processor) {
  if (remN == 1) {
    auto y = n / x;
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
  int size = static_cast<int>(primes.size());
  uint32_t p = 0, nxtRemN;
  int cnt = 0;
  for (; idx < size && static_cast<uint32_t>(primes[idx]) <= remN / primes[idx];
       ++idx) {
    p = primes[idx];
    if (!(remN % p)) {
      cnt = 1;
      break;
    }
  }
  if (!cnt) {
    p = remN;
    cnt = 1;
    nxtRemN = 1;
  } else {
    for (nxtRemN = remN / p; !(nxtRemN % p); ++cnt, nxtRemN /= p) {}
  }
  if (!divisorIterator32Dfs_(idx + 1, primes, x, nxtRemN, n, processor)) {
    return false;
  }
  for (int i = cnt; i > 0; --i) {
    x *= p;
    if (x > n / x) {
      break;
    }
    if (!divisorIterator32Dfs_(idx + 1, primes, x, nxtRemN, n, processor)) {
      return false;
    }
  }
  return true;
}

} // namespace

inline void divisorIterator32(
    uint32_t n,
    const vector<int>& primes,
    const std::function<bool(uint32_t)>& processor) {
  DEBUGF_TRUE(
      primes.back() >= n / primes.back(),
      "Square of largest prime (%lu) should larger than %lu\n",
      primes.back(),
      n);
  divisorIterator32Dfs_(0, primes, 1, n, n, processor);
}

} // namespace math
