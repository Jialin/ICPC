// !macro_gen
// ALL BASE_SPARSE_TABLE_ARRAY_ALL
#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"

using namespace std;

namespace ds {

template<typename V, int MAXBIT, int MAXN>
struct BaseSparseTableArray {
  virtual inline void combine(const V& leftValue, const V& rightValue, V& res) const = 0;

#ifdef BASE_SPARSE_TABLE_ARRAY_RESERVE // ^
  inline void reserve(int capacity) {
    _initLog(capacity);
  }
#endif

  inline void init(vector<V>&& vs) {
    DEBUG_LT(MAXN, 1 << MAXBIT);
    int n = vs.size();
    _initLog(n);
    int m = _log[n] + 1;
    FOR(i, 0, n) {
      _st[0][i] = move(vs[i]);
    }
    FOR(bit, 1, m) {
      int bound = n - (1 << bit) + 1;
      for (int i = 0, ii = 1 << (bit - 1); i < bound; ++i, ++ii) {
        combine(_st[bit - 1][i], _st[bit - 1][ii], _st[bit][i]);
      }
    }
  }

#ifdef BASE_SPARSE_TABLE_ARRAY_CALC // ^
  inline V calc(int l, int r) {
    V res;
    calc(l, r, res);
    return res;
  }
#endif

  inline void calc(int l, int r, V& res) {
    DEBUG_LT(l, r);
    if (l >= r) {
      return;
    }
    int bit = _log[r - l];
    combine(_st[bit][l], _st[bit][r - (1 << bit)], res);
  }

  inline void _initLog(int capacity) {
    int oldSize = _log.size();
    capacity = max(capacity, 1);
    if (capacity <= oldSize) {
      return;
    }
    _log.resize(capacity + 1);
    _log[1] = 0;
    FOR(i, max(2, oldSize), capacity + 1) {
      _log[i] = _log[i >> 1] + 1;
    }
  }

  V _st[MAXBIT][MAXN];
  vector<int> _log;
};

} // namespace ds
