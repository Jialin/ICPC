#pragma once

#include "debug/debug.h"
#include "math/mod/add.h"
#include "math/mod/fix.h"
#include "math/mod/mul.h"

using namespace std;

namespace math {

// Compute nth element in linear recurrence relations.
//   x_n = coef_0 * x_{n-d} + coef_1 * x_{n-d+1} + ... + coef_{d-1} * x_{n-1}
// Given, x_0, ... x_{d-1}, compute x_k
template<typename V = int, typename V_SQR = int64_t>
struct Kitamasa {
  inline Kitamasa() {}

  inline Kitamasa(const vector<V>& coef, const V& mod, int capacity = -1) {
    init(coef, mod, capacity);
  }

  inline void init(const vector<V>& coef, const V& mod, int capacity = -1) {
    _n = static_cast<int>(coef.size());
    _mod = mod;
    _coef.assign(_n, 0);
    for (int i = 0; i < _n; ++i) {
      _coef[i] = fixMod<V>(coef[i], _mod);
    }
    _pows.clear();
    if (capacity > 0) {
      _pows.reserve(capacity);
    }
    _pows.emplace_back(vector<V>(_n));
    if (_n == 1) {
      _pows.back()[0] = _coef[0];
    } else {
      _pows.back()[1] = fixMod<V>(1, _mod);
    }
  }

  // {k} is zero-indexed.
  template<typename K = int64_t>
  inline V calc(const vector<V>& xs, K k) {
    DEBUG_EQ(_n, static_cast<int>(xs.size()));
    _res.assign(_n, 0);
    _res[0] = fixMod(1, _mod);
    for (int i = 0; k; ++i, k >>= 1) {
      if (i >= static_cast<int>(_pows.size())) {
        vector<V> subRes;
        _merge(subRes, _pows[i - 1], _pows[i - 1]);
        _pows.emplace_back(move(subRes));
      }
      if (k & 1) {
        _merge(_tmpRes, _res, _pows[i]);
        swap(_res, _tmpRes);
      }
    }
    V v = 0;
    for (int i = 0; i < _n; ++i) {
      v = addMod<V>(v, mulMod<V, V_SQR>(_res[i], xs[i], _mod), _mod);
    }
    return v;
  }

  inline void _merge(vector<V>& res, const vector<V>& x, const vector<V>& y) {
    res.assign((_n << 1) - 1, 0);
    for (int i = 0; i < _n; ++i) {
      for (int j = 0; j < _n; ++j) {
        res[i + j] =
            addMod<V>(res[i + j], mulMod<V, V_SQR>(x[i], y[j], _mod), _mod);
      }
    }
    for (int i = static_cast<int>(res.size() - 1); i >= _n; --i) {
      for (int j = 0; j < _n; ++j) {
        res[i - _n + j] = addMod<V>(
            res[i - _n + j], mulMod<V, V_SQR>(_coef[j], res[i], _mod), _mod);
      }
    }
    res.resize(_n);
  }

  int _n, _n2;
  V _mod;
  vector<V> _coef, _res, _tmpRes;
  vector<vector<V>> _pows;
};

} // namespace math