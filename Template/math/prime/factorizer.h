#pragma once

#include <cmath>
#include <functional>
#include <vector>

using namespace std;

namespace math {

class Factorizer {
public:
  inline Factorizer(int n) {
    init(n);
  }

  inline void init(int n) {
    int size = (n + 1) >> 1;
    minPrime_.assign(size, 0);
    int bound = static_cast<int>(sqrt(n) + 1);
    for (int i = 3; i <= bound; i += 2) {
      if (minPrime_[i >> 1]) {
        continue;
      }
      for (int j = (i * i) >> 1; j < size; j += i) {
        if (!minPrime_[j]) {
          minPrime_[j] = i;
        }
      }
    }
    minPrimeCnt_.assign(size, 1);
    jump_.assign(size, 1);
    for (int i = 3, j = 1; i < n; i += 2, ++j) {
      if (!minPrime_[j]) {
        minPrime_[j] = i;
        continue;
      }
      int k = i / minPrime_[j], kHalf = k >> 1;
      if (minPrime_[j] == minPrime_[kHalf]) {
        minPrimeCnt_[j] = minPrimeCnt_[kHalf] + 1;
        jump_[j] = jump_[kHalf];
      } else {
        jump_[j] = k;
      }
    }
  }

  inline void factorize(int n, const std::function<bool(int, int)>& processor) {
    int ctz = __builtin_ctz(n);
    if (ctz > 0) {
      if (!processor(2, ctz)) {
        return;
      }
      n >>= ctz;
    }
    int nHalf;
    for (; n > 1; n = jump_[nHalf]) {
      nHalf = n >> 1;
      if (!processor(minPrime_[nHalf], minPrimeCnt_[nHalf])) {
        return;
      }
    }
  }

private:
  vector<int> minPrime_, minPrimeCnt_, jump_;
};

} // namespace math
