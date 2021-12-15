// !macro_gen
// ALL BASE_FENWICK_3D_ARRAY_ALL
#pragma once

#include "common/macros.h"

using namespace std;

namespace ds {

template<typename V, int MAXN, int MAXM, int MAXL>
struct BaseFenwick3DArray {
  virtual inline void _initV(V& v) = 0;

  virtual inline void _addV(V& v, const V& deltaV) = 0;

  inline void init(int n, int m, int l) {
    _n = n;
    _m = m;
    _l = l;
    FOR(i, 0, _n) FOR(j, 0, _m) FOR(k, 0, _l) {
      _initV(_vs[i][j][k]);
    }
  }

  inline void update(int x, int y, int z, const V& deltaV) {
    if (y < _m && z < _l) {
      for (int i = x; i < _n; i |= i + 1) {
        for (int j = y; j < _m; j |= j + 1) {
          for (int k = z; k < _l; k |= k + 1) {
            _addV(_vs[i][j][k], deltaV);
          }
        }
      }
    }
  }

#ifdef BASE_FENWICK_3D_ARRAY_CALC_PREFIX // ^
  inline V calcPrefix(int x, int y, int z) {
    V res;
    // BASE_FENWICK_3D_ARRAY_CALC_PREFIX => _BASE_FENWICK_3D_ARRAY_CALC_PREFIX
    _calcPrefix(x, y, z, res);
    return res;
  }
#endif

#ifdef _BASE_FENWICK_3D_ARRAY_CALC_PREFIX // ^
  inline void _calcPrefix(int x, int y, int z, V& res) {
    _initV(res);
    y = min(y, _m) - 1;
    z = min(z, _l) - 1;
    if (y >= 0 && z >= 0) {
      for (int i = min(x, _n) - 1; i >= 0; --i) {
        for (int j = y; j >= 0; --j) {
          for (int k = z; k >= 0; --k) {
            _addV(res, _vs[i][j][k]);
            k &= k + 1;
          }
          j &= j + 1;
        }
        i &= i + 1;
      }
    }
  }
#endif

#ifdef BASE_FENWICK_3D_ARRAY_CALC_RANGE // ^
  virtual inline void _subV(V& v, const V& deltaV) const = 0;

  inline V calcRange(int x1, int y1, int z1, int x2, int y2, int z2) {
    // BASE_FENWICK_3D_ARRAY_CALC_RANGE => BASE_FENWICK_3D_ARRAY_CALC_PREFIX_RETURN
    if (x1 >= x2 || y1 >= y2 || z1 >= z2 || x1 >= _n || y1 >= _m || z1 >= _l) {
      V res;
      _initV(res);
      return res;
    }
    V res = calcPrefix(x2, y2, z2);
    if (x1 > 0) {
      _subV(res, calcPrefix(x1, y2, z2));
    }
    if (y1 > 0) {
      _subV(res, calcPrefix(x2, y1, z2));
    }
    if (z1 > 0) {
      _subV(res, calcPrefix(x2, y2, z1));
    }
    if (x1 > 0 && y1 > 0) {
      _addV(res, calcPrefix(x1, y1, z2));
    }
    if (x1 > 0 && z1 > 0) {
      _addV(res, calcPrefix(x1, y2, z1));
    }
    if (y1 > 0 && z1 > 0) {
      _addV(res, calcPrefix(x2, y1, z1));
    }
    if (x1 > 0 && y1 > 0 && z1 > 0) {
      _subV(res, calcPrefix(x1, y1, z1));
    }
    return res;
  }
#endif

  int _n, _m, _l;
  V _vs[MAXN][MAXM][MAXL];
};

} // namespace ds
