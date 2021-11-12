// !macro_gen
// ALL DISJOINT_SET_ALL
#pragma once

using namespace std;

namespace ds {

struct DisjointSet {
#ifdef DISJOINT_SET_RESERVE // ^
  inline void reserve(int n) {
    _parents.reserve(n);
  }
#endif

  inline void init(int n) {
    _parents.assign(n, -1);
  }

#ifdef DISJOINT_SET_UNION_SET // ^
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
    return true;
  }
#endif

#ifdef DISJOINT_SET_IS_IN_SAME_SET // ^
  inline bool isInSameSet(int u, int v) {
    return findSet(u) == findSet(v);
  }
#endif

#ifdef DISJOINT_SET_CALC_SET_SIZE // ^
  inline int calcSetSize(int u) {
    return -_parents[findSet(u)];
  }
#endif

  inline int findSet(int v) {
    int& res = _parents[v];
    if (res < 0) {
      return v;
    }
    res = findSet(res);
    return res;
  }

  vector<int> _parents;
};

} // namespace ds
