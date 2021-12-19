// !macro_gen
// ALL BASE_DISJOINT_SET_VALUE_ALL
#pragma once

#include "ds/disjoint_set/base_disjoint_set_value_macros.h"

#include "common/macros.h"

using namespace std;

namespace ds {

template<typename V>
struct BaseDisjointSetValue {
  virtual inline void combine(const V& fromV, V& toV) const = 0;

#ifdef BASE_DISJOINT_SET_VALUE_RESERVE // ^
  inline void reserve(int n) {
    _parents.reserve(n);
  }
#endif

  inline void init(vector<V> vs) {
    _parents.assign(SIZE(vs), -1);
    _vs = move(vs);
  }

  inline bool unionSet(int u, int v) {
    u = findSet(u);
    v = findSet(v);
    if (u == v) {
      return false;
    }
    if (_parents[u] > _parents[v]) {
      swap(u, v);
    }
    _parents[u] += _parents[v];
    _parents[v] = u;
    combine(_vs[v], _vs[u]);
    return true;
  }

  inline const V& calcSetValue(int u) {
    return _vs[findSet(u)];
  }

  inline int findSet(int v) {
    int& res = _parents[v];
    if (res < 0) {
      return v;
    }
    res = findSet(res);
    return res;
  }

  vector<int> _parents;
  vector<V> _vs;
};

} // namespace ds
