#pragma once

#include <functional>

#include "math/fib/fib.h"
#include "math/gcd/gcd32.h"
#include "math/prime/divisor_use_tagger.h"
#include "math/prime/min_prime_tagger.h"

using namespace std;

namespace math {

class PisanoPeriod {
public:
  inline PisanoPeriod() {}

  inline PisanoPeriod(int n, MinPrimeTagger& tagger, bool initTagger = true) {
    init(n, tagger, initTagger);
  }

  inline void init(int n, MinPrimeTagger& tagger, bool initTagger = true) {
    cache_.assign(max(n, 6), -1);
    cache_[1] = 1;
    cache_[2] = 3;
    cache_[5] = 20;
    if (initTagger) {
      tagger.init(n + 1);
    }
    tagger_ = &tagger;
  }

  inline int calcPrime(int p) {
    int& res = cache_[p];
    if (res >= 0) {
      return res;
    }
    auto processor = [&res, p](int period) {
      period <<= 1;
      auto f01 = fib(period, p);
      if (!f01.first && f01.second == 1) {
        res = min(res, period);
      }
      return true;
    };
    int remP = p % 10;
    res = remP == 1 || remP == 9 ? p - 1 : (p + 1) << 1;
    divisorIteratorUseTagger(res >> 1, *tagger_, processor);
    return res;
  }

  inline int calc(int n) {
    int& res = cache_[n];
    if (res >= 0) {
      return res;
    }
    int p, cnt, nxtN;
    tagger_->process(n, p, cnt, nxtN);
    int res1 = 1;
    if (cnt > 1) {
      res1 *= n / nxtN / p;
    }
    res1 *= calcPrime(p);
    int res2 = calc(nxtN);
    res = res1 / gcd32(res1, res2) * res2;
    return res;
  }

private:
  vector<int> cache_;
  MinPrimeTagger* tagger_;
};

} // namespace math
