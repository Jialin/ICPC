// !macro_gen
// ALL BASE_FENWICK_2D_ARRAY_ALL
#pragma once

#include "common/macros.h"

using namespace std;

namespace ds {

template<typename V, int MAXN, int MAXM>
struct BaseFenwick2DArray {
  virtual inline void _initV(V& v) = 0;

  virtual inline void _addV(V& v, const V& deltaV) = 0;

  inline void init(int n, int m) {
    _n = n;
    _m = m;
    FOR(i, 0, _n) FOR(j, 0, _m) {
      _initV(_vs[i][j]);
    }
  }

  inline void update(int x, int y, const V& deltaV) {
    if (y < _m) {
      for (int i = x; i < _n; i |= i + 1) {
        for (int j = y; j < _m; j |= j + 1) {
          _addV(_vs[i][j], deltaV);
        }
      }
    }
  }

#ifdef BASE_FENWICK_2D_ARRAY_CALC_PREFIX // ^
  inline V calcPrefix(int x, int y) {
    V res;
    // BASE_FENWICK_2D_ARRAY_CALC_PREFIX => _BASE_FENWICK_2D_ARRAY_CALC_PREFIX
    _calcPrefix(x, y, res);
    return res;
  }
#endif

#ifdef _BASE_FENWICK_2D_ARRAY_CALC_PREFIX // ^
  inline void _calcPrefix(int x, int y, V& res) {
    _initV(res);
    y = min(y, _m) - 1;
    if (y >= 0) {
      for (int i = min(x, _n) - 1; i >= 0; --i) {
        for (int j = y; j >= 0; --j) {
          _addV(res, _vs[i][j]);
          j &= j + 1;
        }
        i &= i + 1;
      }
    }
  }
#endif

#ifdef BASE_FENWICK_2D_ARRAY_CALC_RANGE // ^
  virtual inline void _subV(V& v, const V& deltaV) const = 0;

  inline V calcRange(int x1, int y1, int x2, int y2) {
    if (x1 >= x2 || y1 >= y2 || x1 >= _n || y1 >= _m) {
      V res;
      _initV(res);
      return res;
    }
    // BASE_FENWICK_2D_ARRAY_CALC_RANGE => BASE_FENWICK_2D_ARRAY_CALC_PREFIX_RETURN
    V res = calcPrefix(x2, y2);
    if (x1 > 0) {
      _subV(res, calcPrefix(x1, y2));
    }
    if (y1 > 0) {
      _subV(res, calcPrefix(x2, y1));
    }
    if (x1 > 0 && y1 > 0) {
      _addV(res, calcPrefix(x1, y1));
    }
    return res;
  }
#endif

  int _n, _m;
  V _vs[MAXN][MAXM];
};

} // namespace ds
