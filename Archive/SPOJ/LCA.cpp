#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define FOR(i,l,r) for(int i=(l);i<(r);++i)

namespace gs { namespace graph {

class UnweightedGraph {
public:
  int n;
  vector<int> lastOut;

  vector<int> nxtOut, toIdx;

  inline int edgeCnt() {
    return static_cast<int>(toIdx.size());
  }

  inline void init(int _n) {
    this->n = _n;
    lastOut.resize(n);
    fill(lastOut.begin(), lastOut.end(), -1);
    nxtOut.clear();
    toIdx.clear();
  }

  inline void addDirected(int x, int y) {
    int edgeIdx = static_cast<int>(nxtOut.size());
    nxtOut.push_back(lastOut[x]);
    toIdx.push_back(y);
    lastOut[x] = edgeIdx;
  }

  inline void addUndirected(int x, int y) {
    addDirected(x, y);
    addDirected(y, x);
  }
}; // class UnweightedGraph
}} // namespace gs::graph

namespace cs { namespace rmq {

template<typename T>
class RMQ {
  int n;
  T* vs;
  vector<vector<int>> rmqIdx;

  static inline int highestBit(int n) {
    return 31 - __builtin_clz(n);
  }

  inline void _init() {
    int bit = highestBit(n);
    rmqIdx.resize(bit + 1);
    for (int i = 0; i <= bit; ++i) rmqIdx[i].resize(n - (1 << i) + 1);
    for (int i = 0; i < n; ++i) rmqIdx[0][i] = i;
    for (int i = 1; i <= bit; ++i) for (int j = n - (1 << i), k = j + (1 << (i - 1)); j >= 0; --j, --k) {
      int jIdx = rmqIdx[i - 1][j];
      int kIdx = rmqIdx[i - 1][k];
      rmqIdx[i][j] = vs[jIdx] < vs[kIdx] ? jIdx : kIdx;
    }
  }
public:
  inline void init(int _n, T* _vs) {
    n = _n;
    vs = _vs;
    _init();
  }

  inline void init(vector<T>& _vs) {
    init(static_cast<int>(_vs.size()), _vs.data());
  }

  inline int calcMinIdx(int lower, int upper) {
    int bit = highestBit(upper - lower + 1);
    int lowerIdx = rmqIdx[bit][lower];
    int upperIdx = rmqIdx[bit][upper - (1 << bit) + 1];
    return vs[lowerIdx] < vs[upperIdx] ? lowerIdx : upperIdx;
  }

  inline T& calcMin(int lower, int upper) {
    return vs[calcMinIdx(lower, upper)];
  }
}; // class RMQ
}} // namespace cs::rmq

namespace trees { namespace lca {

class LCA {
  vector<int> depth, nodeIdx;
  vector<int> in, out;

  gs::graph::UnweightedGraph* tree;
  cs::rmq::RMQ<int> depthRMQ;

  inline void dfs(int _depth, int u, int parent) {
    in[u] = static_cast<int>(depth.size());
    out[u] = in[u];
    depth.push_back(_depth);
    nodeIdx.push_back(u);
    for (int edgeIdx = tree->lastOut[u]; edgeIdx >= 0; edgeIdx = tree->nxtOut[edgeIdx]) {
      int v = tree->toIdx[edgeIdx];
      if (v == parent) continue;
      dfs(_depth + 1, v, u);
      out[u] = static_cast<int>(depth.size());
      depth.push_back(_depth);
      nodeIdx.push_back(u);
    }
  }
public:
  inline void init(gs::graph::UnweightedGraph _tree) {
    tree = &_tree;
    int n = tree->n, n3 = n * 3;
    depth.clear(); depth.reserve(n3);
    nodeIdx.clear(); nodeIdx.reserve(n3);
    in.clear(); in.reserve(n);
    out.clear(); out.reserve(n);
    dfs(0, 0, -1);
    depthRMQ.init(depth);
  }

  inline int calc(int x, int y) {
    int idx = depthRMQ.calcMinIdx(min(in[x], in[y]), max(out[x], out[y]));
    return nodeIdx[idx];
  }
}; // class LCA
}} // namespace trees::lca

gs::graph::UnweightedGraph tree;
trees::lca::LCA lca;

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int n; scanf("%d", &n);
    tree.init(n);
    FOR(i, 0, n) {
      int m; scanf("%d", &m);
      FOR(j, 0, m) {
        int x; scanf("%d", &x);
        tree.addUndirected(i, x - 1);
      }
    }
    printf("Case %d:\n", taskIdx);
    lca.init(tree);
    int q; scanf("%d", &q);
    FOR(i, 0, q) {
      int x, y; scanf("%d%d", &x, &y);
      printf("%d\n", lca.calc(x - 1, y - 1) + 1);
    }
  }
  return 0;
}
