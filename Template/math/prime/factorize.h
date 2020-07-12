#pragma once

#include "math/prime/min_prime_tagger.h"
#include <functional>

using namespace std;

namespace math {

inline void factorize(
    int n,
    const MinPrimeTagger& tagger,
    const std::function<bool(int, int)>& processor) {
  while (n > 1) {
    int p, cnt;
    tagger.process(n, p, cnt, n);
    if (!processor(p, cnt)) {
      return;
    }
  }
}

} // namespace math
