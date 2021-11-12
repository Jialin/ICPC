// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

namespace ds {

template<typename V>
struct DisjointSetMax {
#ifdef DISJOINT_SET_SIZE_MAX_RESERVE // ^
  inline void reserve(int n) {
    _parents.reserve(n);
  }
#endif

  inline void init(vector<V>&& vs) {
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
    _vs[u] = max(_vs[u], _vs[v]);
    return true;
  }

  inline const V& calcMaxValue(int u) {
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

int main() {
  int n, m;
  io::readInt(n);
  io::readInt(m);
  vector<int> ls(m), rs(m), cs(m);
  FOR(i, 0, m) {
    io::readInt(ls[i]);
    io::readInt(rs[i]);
    io::readInt(cs[i]);
    --ls[i];
  }
  vector<int> nxtIdx(n);
  FOR(i, 0, n) {
    nxtIdx[i] = i + 1;
  }
  ds::DisjointSetMax<int> dset;
  dset.init(move(nxtIdx));
  vector<int> colors(n);
  for (int i = m - 1; i >= 0; --i) {
    int prev = -1, cur = ls[i];
    while (cur < rs[i]) {
      if (!colors[cur]) {
        colors[cur] = cs[i];
      }
      if (prev >= 0) {
        dset.unionSet(prev, cur);
      }
      prev = cur;
      cur = dset.calcMaxValue(cur);
    }
  }
  FOR(i, 0, n) {
    io::writeInt(colors[i]);
    io::writeChar('\n');
  }
}
