#pragma once

#include <vector>

#include "math/mod/add.h"
#include "math/mod/combination.h"
#include "math/mod/exp.h"
#include "math/mod/fix.h"
#include "math/mod/inv.h"
#include "math/mod/mul.h"
#include "math/mod/sub.h"

using namespace std;

namespace math {

namespace {

// Represents <a>+sqrt(5)*<b> (mod <mod>)
struct _FibPartMod {
  inline _FibPartMod() {}

  inline _FibPartMod(int a_, int b_, int mod) {
    init(a_, b_, mod);
  }

  inline void init(int a_, int b_, int mod) {
    _mod = mod;
    a = fixMod(a_, mod);
    b = fixMod(b_, mod);
  }

  inline void init(const _FibPartMod& o) {
    init(o.a, o.b, o._mod);
  }

  inline void operator-=(const _FibPartMod& o) {
    a = subMod(a, o.a, _mod);
    b = subMod(b, o.b, _mod);
  }

  inline void operator+=(const _FibPartMod& o) {
    a = addMod(a, o.a, _mod);
    b = addMod(b, o.b, _mod);
  }

  inline void operator+=(const int delta) {
    a = addMod(a, fixMod(delta, _mod), _mod);
  }

  inline void operator*=(const _FibPartMod& o) {
    int resA = addMod(
        mulMod(a, o.a, _mod),
        mulMod(mulMod(b, o.b, _mod), fixMod(5, _mod), _mod),
        _mod);
    int resB = addMod(mulMod(a, o.b, _mod), mulMod(b, o.a, _mod), _mod);
    a = resA;
    b = resB;
  }

  inline void operator*=(const int scale) {
    a = mulMod(a, fixMod(scale, _mod), _mod);
    b = mulMod(b, fixMod(scale, _mod), _mod);
  }

  int a, b;
  int _mod;
};

} // namespace

struct FibPowerSum {
  inline FibPowerSum(int mod, int expBound = -1) {
    init(mod, expBound);
  }

  inline void init(int mod, int expBound = -1) {
    int inv2 = invMod(2, mod);
    _mod = mod;
    if (expBound >= 0) {
      as_.reserve(expBound);
      bs_.reserve(expBound);
    }
    as_.clear();
    bs_.clear();
    as_.emplace_back(1, 0, mod);
    bs_.emplace_back(1, 0, mod);
    as_.emplace_back(inv2, inv2, mod);
    bs_.emplace_back(inv2, inv2 ? mod - inv2 : 0, mod);
    for (int i = 2; i < expBound; ++i) {
      as_.emplace_back(as_.back());
      as_.back() *= as_[1];
      bs_.emplace_back(bs_.back());
      bs_.back() *= bs_[1];
    }
    _comb.init(expBound, mod);
    _inv5 = invMod(fixMod(5, mod), mod);
  }

  // Computes sum{F(i)^<exp> where i from 0 to n}
  template<typename T>
  inline int calc(T n, int exp) {
    ++n;
    _FibPartMod res(0, 0, _mod), base, mul, subRes, subRes2;
    for (int i = 0; i <= exp; ++i) {
      T mask = 1;
      for (; mask <= n; mask <<= 1) {}
      base.init(as_[i]);
      base *= bs_[exp - i];
      mul.init(base);
      subRes.init(as_[0]);
      for (mask >>= 2; mask; mask >>= 1) {
        subRes2.init(subRes);
        subRes2 *= mul;
        subRes2 += subRes;
        mul *= mul;
        if (n & mask) {
          subRes2 *= base;
          subRes2 += 1;
          mul *= base;
        }
        subRes.init(subRes2);
      }
      subRes *= _comb.calc(exp, i);
      if ((exp - i) & 1) {
        res -= subRes;
      } else {
        res += subRes;
      }
    }
    return mulMod(
        (exp & 1) ? res.b : res.a, expMod(_inv5, exp >> 1, _mod), _mod);
  }

  vector<_FibPartMod> as_, bs_;
  CombinationMod _comb;
  int _inv5, _mod;
};

} // namespace math
