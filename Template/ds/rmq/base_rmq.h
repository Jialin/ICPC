// !macro_gen
// ALL BASE_RMQ_ALL
#pragma once

#include "common/macros.h"

using namespace std;

namespace ds {

template<typename V>
struct BaseRMQ {
  virtual inline void combine(const V& leftValue, const V& rightValue, V& res) const = 0;

#ifdef BASE_RMQ_RESERVE // ^
  inline void reserve(int capacity) {
    _fs.reserve(capacity);
    _initLog(capacity);
  }
#endif

  inline void init(vector<V>&& vs) {
    int n = vs.size();
    _initLog(n);
    int m = _log[n] + 1;
    _fs.resize(m);
    _fs[0] = move(vs);
    FOR(bit, 1, m) {
      int size = n - (1 << bit) + 1;
      if (_fs[bit].size() < size) {
        _fs[bit].resize(size);
      }
      FOR(i, 0, size) {
        combine(_fs[bit - 1][i], _fs[bit - 1][i + (1 << (bit - 1))], _fs[bit][i]);
      }
    }
  }

  inline void calc(int l, int r, V& res) {
    int bit = _log[r - l];
    combine(_fs[bit][l], _fs[bit][r - (1 << bit)], res);
  }

  inline void _initLog(int capacity) {
    int oldSize = _log.size();
    if (capacity <= oldSize) {
      return;
    }
    _log.resize(capacity + 1);
    _log[1] = 0;
    FOR(i, max(2, oldSize), capacity + 1) {
      _log[i] = _log[i >> 1] + 1;
    }
  }

  vector<vector<V>> _fs;
  vector<int> _log;
};

} // namespace ds
