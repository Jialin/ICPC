#pragma once

#include "debug/debug.h"

using namespace std;

namespace math {

// Compute nth element in linear recurrence relations.
//   x_n = (coef_0 & x_{n-d})     \
//       ^ (coef_1 & x_{n-d+1})   \
//       ^ ...                    \
//       ^ (coef_{d-1} & x_{n-1})
// Given, x_0, ... x_{d-1}, compute x_k
template<typename V = uint32_t>
struct KitamasaAndXor {
  template<typename K = int>
  inline V calc(const vector<V>& coefs, const vector<V>& xs, K k) {
    DEBUG_GE(k, 0);
    _n = static_cast<int>(coefs.size());
    _n21 = (_n << 1) - 1;
    _tmpRes.resize(_n21);
    _calc(coefs, k);
    V v = 0;
    for (int i = 0; i < _n; ++i) {
      v ^= _res[i] & xs[i];
    }
    return v;
  }

  template<typename K = int>
  inline void _calc(const vector<V>& coefs, K k) {
    if (k < _n) {
      _res.assign(_n, 0);
      _res[k] = ~static_cast<V>(0);
      return;
    }
    if (k & 1) {
      _calc(coefs, k - 1);
      V lastRes = _res[_n - 1];
      for (int i = _n - 1; i > 0; --i) {
        _res[i] = _res[i - 1] ^ (lastRes & coefs[i]);
      }
      _res[0] = lastRes & coefs[0];
    } else {
      _calc(coefs, k >> 1);
      _tmpRes.assign(_n21, 0);
      for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n; ++j) {
          _tmpRes[i + j] ^= _res[i] & _res[j];
        }
      }
      for (int i = _n21 - 1; i >= _n; --i) {
        V v = _tmpRes[i];
        for (int j = 0; j < _n; ++j) {
          _tmpRes[i - _n + j] ^= v & coefs[j];
        }
      }
      for (int i = 0; i < _n; ++i) {
        _res[i] = _tmpRes[i];
      }
    }
  }

  int _n, _n21;
  vector<V> _res, _tmpRes;
};

} // namespace math
