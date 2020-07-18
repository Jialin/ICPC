#pragma once

#include <vector>

#include "math/prime/divisor64.h"

using namespace std;

namespace math {

class PhiInv64 {
public:
  inline PhiInv64()
      : processor_([this](uint64_t divisor) {
          ++divisor;
          if (millerRabin64(divisor)) {
            primes_.push_back(divisor);
          }
          return true;
        }) {}

  inline void calc(uint64_t n, const function<void(uint64_t)>& processor) {
    if (n == 1) {
      processor(1);
      processor(2);
      return;
    }
    if (n & 1) {
      return;
    }
    primes_.clear();
    divisorIterator64(n, processor_);
    sort(primes_.begin(), primes_.end());
    if (!primes_.empty()) {
      dfs_(static_cast<int>(primes_.size()) - 1, n, 1, processor);
    }
  }

private:
  // When computing min/max inverse phi, we could use DP to speed up
  //   dp[i][j]: use the first i divisor,
  //             dp[i][j] is the min/max value of phiInv(divisor[j])
  inline void dfs_(
      int idx,
      uint64_t remN,
      uint64_t v,
      const function<void(uint64_t)>& processor) {
    if (remN == 1) {
      processor(v);
      processor(v << 1);
      return;
    }
    if (remN & 1) {
      return;
    }
    if (!idx) {
      int shift = __builtin_ctzll(remN);
      if (remN == 1ULL << shift) {
        processor(v << (shift + 1));
      }
      return;
    }
    uint64_t p = primes_[idx];
    if (!(remN % (p - 1))) {
      if (!(remN % p)) {
        for (remN /= p, v *= p; !(remN % p); remN /= p, v *= p) {}
        dfs_(idx - 1, remN / (p - 1), v * p, processor);
        return;
      } else {
        dfs_(idx - 1, remN / (p - 1), v * p, processor);
      }
    }
    dfs_(idx - 1, remN, v, processor);
  }

  vector<uint64_t> primes_;
  function<bool(uint64_t)> processor_;
};

} // namespace math
