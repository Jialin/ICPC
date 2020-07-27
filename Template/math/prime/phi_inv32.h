#pragma once

#include <functional>
#include <vector>

#include "math/prime/divisor32.h"
#include "math/prime/miller_rabin32.h"

using namespace std;

namespace math {

class PhiInv32 {
public:
  inline PhiInv32(const vector<int>& primes)
      : primes_(&primes), processor_([this](uint32_t divisor) {
          ++divisor;
          if (millerRabin32(divisor)) {
            candidates_.push_back(divisor);
          }
          return true;
        }) {}

  inline void calc(uint32_t n, const function<void(uint64_t)>& processor) {
    if (n == 1) {
      processor(1);
      processor(2);
      return;
    }
    if (n & 1) {
      return;
    }
    candidates_.clear();
    divisorIterator32(n, *primes_, processor_);
    sort(candidates_.begin(), candidates_.end());
    if (!candidates_.empty()) {
      dfs_(static_cast<int>(candidates_.size()) - 1, n, 1, processor);
    }
  }

private:
  inline void dfs_(
      int idx,
      uint32_t remN,
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
      int shift = __builtin_ctz(remN);
      if (remN == 1U << shift) {
        processor(v << (shift + 1));
      }
      return;
    }
    auto p = candidates_[idx];
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

  vector<uint32_t> candidates_;
  const vector<int>* primes_;
  function<bool(uint64_t)> processor_;
};

} // namespace math
