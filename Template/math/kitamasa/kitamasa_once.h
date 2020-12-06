#pragma once

#include "debug/debug.h"
#include "math/mod/accumulator.h"
#include "math/mod/add.h"
#include "math/mod/fix.h"
#include "math/mod/mul.h"

using namespace std;

namespace math {

// Compute nth element in linear recurrence relations.
//   x_n = coef_0 * x_{n-d} + coef_1 * x_{n-d+1} + ... + coef_{d-1} * x_{n-1}
// Given, x_0, ... x_{d-1}, compute x_k
template<typename V = int, typename V_SQR = int64_t>
struct KitamasaOnce {
  template<typename K = int>
  inline V calc(const vector<V>& coefs, const vector<V>& xs, K k, V mod) {
    DEBUG_TRUE(k >= 0, "k(%d) should be non-negative.", k);
    _n = static_cast<int>(coefs.size());
    _n21 = (_n << 1) - 1;
    _mod = mod;
    _tmpRes.reserve(_n21);
    for (int i = 0; i < _n21; ++i) {
      _tmpRes.emplace_back(_mod);
    }
    _calc(coefs, k);
    V v = 0;
    for (int i = 0; i < _n; ++i) {
      v = addMod<V>(v, mulMod<V, V_SQR>(_res[i], xs[i], _mod), _mod);
    }
    return v;
  }

  template<typename K = int>
  inline void _calc(const vector<V>& coefs, K k) {
    if (k < _n) {
      _res.assign(_n, 0);
      _res[k] = fixMod<V>(1, _mod);
      return;
    }
    if (k & 1) {
      _calc(coefs, k - 1);
      V lastRes = _res[_n - 1];
      for (int i = _n - 1; i > 0; --i) {
        _res[i] = addMod<V>(
            _res[i - 1], mulMod<V, V_SQR>(lastRes, coefs[i], _mod), _mod);
      }
      _res[0] = mulMod<V, V_SQR>(lastRes, coefs[0], _mod);
    } else {
      _calc(coefs, k >> 1);
      for (int i = 0; i < _n21; ++i) {
        _tmpRes[i].reset(0);
      }
      for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n; ++j) {
          _tmpRes[i + j].add(static_cast<V_SQR>(_res[i]) * _res[j]);
        }
      }
      for (int i = _n21 - 1; i >= _n; --i) {
        V_SQR v = _tmpRes[i].get();
        for (int j = 0; j < _n; ++j) {
          _tmpRes[i - _n + j].add(v * coefs[j]);
        }
      }
      for (int i = 0; i < _n; ++i) {
        _res[i] = _tmpRes[i].get();
      }
    }
  }

  int _n, _n21;
  V _mod;
  vector<V> _res;
  vector<AccumulatorMod<V_SQR>> _tmpRes;
};

} // namespace math