// !macro_gen
// ALL MIN_PRIME_TAGGER_ALL
#pragma once

#ifdef UNITTEST
#include <cmath>
#endif

using namespace std;

namespace math {

struct MinPrimeTagger {
#ifdef MIN_PRIME_TAGGER_RESERVE // ^
  inline void reserve(int n) {
    n = (n + 1) >> 1;
    _minPrimes.reserve(n);
  }
#endif

  inline void init(int n) {
    int size = (n + 1) >> 1;
    _minPrimes.assign(size, 0);
    int bound = static_cast<int>(sqrt(n) + 1);
    for (int i = 3; i <= bound; i += 2) {
      if (_minPrimes[i >> 1]) {
        continue;
      }
      for (int j = (i * i) >> 1; j < size; j += i) {
        if (!_minPrimes[j]) {
          _minPrimes[j] = i;
        }
      }
    }
    _minPrimeCnts.assign(size, 1);
    _jumps.assign(size, 1);
    for (int i = 3, j = 1; i <= n; i += 2, ++j) {
      if (!_minPrimes[j]) {
        _minPrimes[j] = i;
        continue;
      }
      int k = i / _minPrimes[j], kHalf = k >> 1;
      if (_minPrimes[j] == _minPrimes[kHalf]) {
        _minPrimeCnts[j] = _minPrimeCnts[kHalf] + 1;
        _jumps[j] = _jumps[kHalf];
      } else {
        _jumps[j] = k;
      }
    }
  }

  inline void process(int n, int& prime, int& primeCnt, int& nxtN) const {
    if (n & 1) {
      prime = _minPrimes[n >> 1];
      primeCnt = _minPrimeCnts[n >> 1];
      nxtN = _jumps[n >> 1];
    } else {
      prime = 2;
      primeCnt = __builtin_ctz(n);
      nxtN = n >> primeCnt;
    }
  }

  vector<int> _minPrimes, _minPrimeCnts, _jumps;
};

} // namespace math
