// !macro_gen
// ALL DISJOINT_SET_SIZE_GROUPS_ALL
#pragma once

using namespace std;

namespace ds {

// Each node belongs to one of the group [0, groupCnt), and group diff equals to group index
// difference mod <groupCnt>
struct DisjointSetSizeGroups {
#ifdef DISJOINT_SET_SIZE_GROUPS_RESERVE // ^
  inline void reserve(int n) {
    _parents.reserve(n);
    _diffs.reserve(n);
  }
#endif

  inline void init(int n, int groupCnt) {
    _groupCnt = groupCnt;
    _parents.assign(n, -1);
    _diffs.assign(n, 0);
  }

  inline bool unionSet(int u, int v, int groupDiff, bool& valid) {
    int rootU = findSet(u);
    int rootV = findSet(v);
    if (rootU == rootV) {
      valid = _diffs[u] == calcSum(groupDiff, _diffs[v]);
      return false;
    }
    if (_parents[rootU] > _parents[rootV]) {
      swap(rootU, rootV);
      swap(u, v);
      if (groupDiff) {
        groupDiff = _groupCnt - groupDiff;
      }
    }
    _parents[rootU] += _parents[rootV];
    _parents[rootV] = rootU;
    _diffs[rootV] = calcDiff(_diffs[u], calcSum(groupDiff, _diffs[v]));
    valid = true;
    return true;
  }

#ifdef DISJOINT_SET_SIZE_GROUPS_IS_IN_SAME_SET // ^
  inline bool isInSameSet(int u, int v) {
    return findSet(u) == findSet(v);
  }
#endif

#ifdef DISJOINT_SET_SIZE_GROUPS_CALC_GROUP_DIFF // ^
  inline int calcGroupDiff(int u, int v) {
    if (findSet(u) != findSet(v)) {
      return -1;
    }
    return calcDiff(_diffs[u], _diffs[v]);
  }
#endif

  inline int findSet(int u) {
    int parentU = _parents[u];
    if (parentU < 0) {
      return u;
    }
    _parents[u] = findSet(parentU);
    _diffs[u] = calcSum(_diffs[u], _diffs[parentU]);
    return _parents[u];
  }

  inline int calcDiff(int x, int y) const {
    x -= y;
    return x < 0 ? x + _groupCnt : x;
  }

  inline int calcSum(int x, int y) const {
    x += y;
    return x >= _groupCnt ? x - _groupCnt : x;
  }

  int _groupCnt;
  vector<int> _parents, _diffs;
};

} // namespace ds
