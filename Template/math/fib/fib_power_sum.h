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

  inline void operator-=(int delta) {
    a = subMod(a, fixMod(delta, _mod), _mod);
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
    _five = fixMod(5, mod);
    _inv5 = invMod(_five, mod);
    _zeroPart.init(0, 0, mod);
    _onePart.init(fixMod(1, mod), 0, mod);
    int inv2 = invMod(2, mod);
    _mod = mod;
    if (expBound >= 0) {
      as_.reserve(expBound);
      bs_.reserve(expBound);
    }
    as_.clear();
    bs_.clear();
    as_.emplace_back(_onePart);
    bs_.emplace_back(_onePart);
    as_.emplace_back(inv2, inv2, mod);
    bs_.emplace_back(inv2, inv2 ? mod - inv2 : 0, mod);
    for (int i = 2; i < expBound; ++i) {
      as_.emplace_back(as_.back());
      as_.back() *= as_[1];
      bs_.emplace_back(bs_.back());
      bs_.back() *= bs_[1];
    }
    _comb.init(expBound, mod);
  }

  // Computes sum{F(i)^<exp> where i from 0 to n}
  template<typename T>
  inline int calc(T n, int exp) {
    _res.init(_zeroPart);
    for (int i = 0; i <= exp; ++i) {
      _base.init(as_[i]);
      _base *= bs_[exp - i];
      if (_base.a == 1 && !_base.b) {
        _subRes.init(static_cast<int>(fixMod<T>(n + 1, _mod)), 0, _mod);
      } else {
        _mul.init(_base);
        _subRes.init(_onePart);
        for (T tmpN = n + 1; tmpN; tmpN >>= 1) {
          if (tmpN & 1) {
            _subRes *= _mul;
          }
          _mul *= _mul;
        }
        _subRes -= 1;
        _base -= 1;
        int scale = subMod(
            mulMod(_base.a, _base.a, _mod),
            mulMod(mulMod(_base.b, _base.b, _mod), _five, _mod),
            _mod);
        _subRes *= invMod(scale, _mod);
        _base.b = _base.b ? _mod - _base.b : 0;
        _subRes *= _base;
      }
      _subRes *= _comb.calc(exp, i);
      if ((exp - i) & 1) {
        _res -= _subRes;
      } else {
        _res += _subRes;
      }
    }
    return mulMod(
        (exp & 1) ? _res.b : _res.a, expMod(_inv5, exp >> 1, _mod), _mod);
  }

  vector<_FibPartMod> as_, bs_;
  CombinationMod _comb;
  _FibPartMod _zeroPart, _onePart, _res, _base, _mul, _subRes;
  int _inv5, _five, _mod;
};

} // namespace math
