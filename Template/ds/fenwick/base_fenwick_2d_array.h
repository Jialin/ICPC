// !macro_gen
// ALL BASE_FENWICK_2D_ARRAY_ALL
#pragma once

#include "common/macros.h"

using namespace std;

namespace ds {

template<typename V, int MAXN, int MAXM>
struct BaseFenwick2DArray {
  virtual inline void initV(V& v) = 0;

  virtual inline void updateV(V& v, const V& deltaV) = 0;

  inline void init(int n, int m) {
    _n = n;
    _m = m;
    FOR(i, 0, _n) FOR(j, 0, _m) {
      initV(_vs[i][j]);
    }
  }

  inline void update(int x, int y, const V& deltaV) {
    for (int i = x; i < _n; i |= i + 1) {
      for (int j = y; j < _m; j |= j + 1) {
        updateV(_vs[i][j], deltaV);
      }
    }
  }

#ifdef BASE_FENWICK_2D_ARRAY_CALC_PREFIX_RETURN // ^
  inline V calcPrefix(int x, int y) {
    V res;
    calcPrefix(x, y, res);
    return res;
  }
#endif

  inline void calcPrefix(int x, int y, V& res) {
    initV(res);
    for (int i = x; i >= 0; --i) {
      for (int j = y; j >= 0; --j) {
        updateV(res, _vs[i][j]);
        j &= j + 1;
      }
      i &= i + 1;
    }
  }

#ifdef BASE_FENWICK_2D_ARRAY_CALC_RANGE // ^
  virtual inline V subV(const V& upperV, const V& lowerV) const = 0;

  inline V calcRange(int x1, int y1, int x2, int y2) {
    // BASE_FENWICK_2D_ARRAY_CALC_RANGE => BASE_FENWICK_2D_ARRAY_CALC_PREFIX_RETURN
    V res = calcPrefix(x2 - 1, y2 - 1);
    if (x1) {
      res = subV(res, calcPrefix(x1 - 1, y2 - 1));
    }
    if (y1) {
      res = subV(res, calcPrefix(x2 - 1, y1 - 1));
    }
    if (x1 && y1) {
      updateV(res, calcPrefix(x1 - 1, y1 - 1));
    }
    return res;
  }
#endif

  int _n, _m;
  V _vs[MAXN][MAXM];
};

} // namespace ds
