#pragma once

#include <functional>

#include "math/fib/pisano_period.h"
#include "math/gcd64.h"
#include "math/prime/divisor64.h"
#include "math/prime/factorize64.h"

using namespace std;

namespace math {

class PisanoPeriod64 {
public:
  inline PisanoPeriod64(
      int cacheBound, MinPrimeTagger& tagger, bool init = true) {
    cacheBound_ = max(cacheBound, 6);
    pp_.init(static_cast<int>(cacheBound_), tagger, init);
  }

  inline uint64_t calcPrime(uint64_t p) {
    if (p < cacheBound_) {
      return pp_.calcPrime(static_cast<int>(p));
    }
    auto processor = [this](uint64_t period) {
      periods_.push_back(period << 1);
      return true;
    };
    int remP = p % 10;
    periods_.clear();
    divisorIterator64(remP == 1 || remP == 9 ? (p - 1) >> 1 : p + 1, processor);
    sort(periods_.begin(), periods_.end());
    for (auto period : periods_) {
      auto f01 = fib<uint64_t, uint64_t, __uint128_t>(period, p);
      if (!f01.first && f01.second == 1) {
        return period;
      }
    }
    assert(false);
    return 0;
  }

  inline uint64_t calc(uint64_t n) {
    if (n < cacheBound_) {
      return pp_.calc(static_cast<int>(n));
    }
    uint64_t res = 1;
    auto processor = [this, &res](uint64_t p, int cnt) {
      uint64_t subRes = calcPrime(p);
      for (int i = 1; i < cnt; ++i) {
        subRes *= p;
      }
      res = res / gcd64(res, subRes) * subRes;
    };
    factorize64(n, processor);
    return res;
  }

private:
  uint64_t cacheBound_;
  PisanoPeriod pp_;
  vector<uint64_t> periods_;
};

} // namespace math
