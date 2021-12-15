// !macro_gen
// ALL BASE_SPARSE_TABLE_ALL
#pragma once

#include "common/macros.h"
#include "debug/debug_basic.h"

using namespace std;

namespace ds {

template<typename V>
struct BaseSparseTable {
  virtual inline void combine(const V& lv, const V& rv, V& res) const = 0;

#ifdef BASE_SPARSE_TABLE_RESERVE // ^
  inline void reserve(int capacity) {
    _st.reserve(capacity);
    _initLog(capacity);
  }
#endif

  inline void init(vector<V>&& vs) {
    int n = vs.size();
    _initLog(n);
    int m = _log[n] + 1;
    _st.resize(m);
    _st[0] = move(vs);
    FOR(bit, 1, m) {
      int size = n - (1 << bit) + 1;
      if (_st[bit].size() < size) {
        _st[bit].resize(size);
      }
      FOR(i, 0, size) {
        combine(_st[bit - 1][i], _st[bit - 1][i + (1 << (bit - 1))], _st[bit][i]);
      }
    }
  }

#ifdef BASE_SPARSE_TABLE_CALC // ^
  inline V calc(int l, int r) {
    V res;
    // BASE_SPARSE_TABLE_CALC => _BASE_SPARSE_TABLE_CALC
    _calc(l, r, res);
    return res;
  }
#endif

#ifdef _BASE_SPARSE_TABLE_CALC // ^
  inline void _calc(int l, int r, V& res) {
    DEBUG_LT(l, r);
    if (l >= r) {
      return;
    }
    int bit = _log[r - l];
    combine(_st[bit][l], _st[bit][r - (1 << bit)], res);
  }
#endif

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

  vector<vector<V>> _st;
  vector<int> _log;
};

} // namespace ds
