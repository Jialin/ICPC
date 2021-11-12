// !macro_gen
// ALL DISJOINT_SET_PARITY_ALL
#pragma once

using namespace std;

namespace ds {

struct DisjointSetParity {
#ifdef DISJOINT_SET_PARITY_RESERVE // ^
  inline void reserve(int n) {
    _parents.reserve(n);
    _parities.reserve(n);
  }
#endif

  inline void init(int n) {
    _parents.assign(n, -1);
    _parities.assign(n, false);
  }

  inline bool unionSet(int u, int v, bool parity, bool& valid) {
    int rootU = findSet(u);
    int rootV = findSet(v);
    if (rootU == rootV) {
      valid = (_parities[u] ^ _parities[v]) == parity;
      return false;
    }
    if (_parents[rootU] > _parents[rootV]) {
      swap(rootU, rootV);
      swap(u, v);
    }
    _parents[rootU] += _parents[rootV];
    _parents[rootV] = rootU;
    _parities[rootV] = _parities[u] ^ _parities[v] ^ parity;
    valid = true;
    return true;
  }

#ifdef DISJOINT_SET_PARITY_IS_IN_SAME_SET // ^
  inline bool isInSameSet(int u, int v) {
    return findSet(u) == findSet(v);
  }
#endif

#ifdef DISJOINT_SET_PARITY_IS_SAME_PARITY // ^
  inline bool isSameParity(int u, int v) {
    if (findSet(u) != findSet(v)) {
      return false;
    }
    return _parities[u] ^ _parities[v];
  }
#endif

  inline int findSet(int u) {
    int parentU = _parents[u];
    if (parentU < 0) {
      return u;
    }
    _parents[u] = findSet(parentU);
    _parities[u] = _parities[u] ^ _parities[parentU];
    return _parents[u];
  }

  vector<int> _parents;
  vector<bool> _parities;
};

} // namespace ds
