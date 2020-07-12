#pragma once

#include <cmath>
#include <vector>

using namespace std;

namespace math {

class MinPrimeTagger {
public:
  inline MinPrimeTagger() {}

  inline MinPrimeTagger(int n) {
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

  inline void process(int n, int& prime, int& primeCnt, int& nxtN) const {
    if (n & 1) {
      prime = minPrime_[n >> 1];
      primeCnt = minPrimeCnt_[n >> 1];
      nxtN = jump_[n >> 1];
    } else {
      prime = 2;
      primeCnt = __builtin_ctz(n);
      nxtN = n >> primeCnt;
    }
  }

private:
  vector<int> minPrime_, minPrimeCnt_, jump_;
};

} // namespace math
