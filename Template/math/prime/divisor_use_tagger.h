#pragma once

#include <functional>

#include "math/prime/min_prime_tagger.h"

using namespace std;

namespace math {

namespace {

inline bool _divisorIteratorUseTagger(
    int x,
    int remN,
    int n,
    const MinPrimeTagger& tagger,
    const std::function<bool(int)>& processor) {
  if (remN == 1) {
    int y = n / x;
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
  int p, cnt, nxtRemN;
  tagger.process(remN, p, cnt, nxtRemN);
  if (!_divisorIteratorUseTagger(x, nxtRemN, n, tagger, processor)) {
    return false;
  }
  for (int i = cnt; i > 0; --i) {
    x *= p;
    if (x > n / x) {
      break;
    }
    if (!_divisorIteratorUseTagger(x, nxtRemN, n, tagger, processor)) {
      return false;
    }
  }
  return true;
}

} // namespace

inline void divisorIteratorUseTagger(
    int n,
    const MinPrimeTagger& tagger,
    const std::function<bool(int)>& processor) {
  _divisorIteratorUseTagger(1, n, n, tagger, processor);
}

} // namespace math
