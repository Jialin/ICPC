#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

template<class T> using MINHEAP = priority_queue<T, vector<T>, greater<T>>;
using LL = long long;
using ULL = unsigned long long;

#define CAST static_cast
#define SIZE(v) (CAST<int>((v).size()))
#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),x)-BEGIN(v)
#define FOR(i,l,r) for(int i=(l);i<(r);++i)

namespace gs {

class UnweightedGraph {
public:
  inline void init(int n) {
    n_ = n;
    lastOut_.resize(n);
    fill(lastOut_.begin(), lastOut_.end(), -1);
    nxtOut_.clear();
    toIdx_.clear();
  }

  inline void addDirected(int x, int y) {
    int edgeIdx = SIZE(nxtOut_);
    nxtOut_.push_back(lastOut_[x]);
    toIdx_.push_back(y);
    lastOut_[x] = edgeIdx;
  }

  inline void addUndirected(int x, int y) {
    addDirected(x, y);
    addDirected(y, x);
  }

  inline int n() const { return n_; }
  inline int edgeCnt() const { return SIZE(toIdx_); }
  inline int lastOut(int x) const { return lastOut_[x]; }
  inline int nxtOut(int x) const { return nxtOut_[x]; }
  inline int toIdx(int x) const { return toIdx_[x]; }

private:
  int n_;
  vector<int> lastOut_, nxtOut_, toIdx_;
}; // class UnweightedGraph
} // namespace gs

namespace cs {

template<typename V>
class Vector2D {
public:
  inline void init(int n, int m = -1) {
    n_ = n;
    lastOut_.resize(n); fill(lastOut_.begin(), lastOut_.end(), -1);
    nxtOut_.clear(); if (m >= 0) nxtOut_.reserve(m);
    vs_.clear(); if (m >= 0) vs_.reserve(m);
  }

  inline void add(int x, const V& v) {
    int edgeIdx = SIZE(nxtOut_);
    nxtOut_.push_back(lastOut_[x]);
    lastOut_[x] = edgeIdx;
    vs_.push_back(v);
  }

  inline int n() const { return n_; }
  inline int lastOut(int x) const { return lastOut_[x]; }
  inline int nxtOut(int x) const { return nxtOut_[x]; }
  inline int value(int x) const { return vs_[x]; }

private:
  int n_;
  vector<int> lastOut_, nxtOut_;
  vector<V> vs_;
}; // class Vector2D
} // namespace cs

namespace cs {

class DisjointSet {
public:
  inline void init(int n) {
    p_.resize(n);
    fill(p_.begin(), p_.end(), -1);
  }

  inline int calcRoot(int x) {
    int root = x;
    for ( ; p_[root] >= 0; root = p_[root]) {}
    while (p_[x] >= 0) {
      int tmp = p_[x];
      p_[x] = root;
      x = tmp;
    }
    return root;
  }

  inline bool setFriend(int x, int y) {
    int rootX = calcRoot(x);
    int rootY = calcRoot(y);
    if (rootX != rootY) {
      if (p_[rootX] > p_[rootY]) swap(rootX, rootY);
      p_[rootX] += p_[rootY];
      p_[rootY] = rootX;
      return true;
    } else {
      return false;
    }
  }

  inline bool isFriend(int x, int y) {
    return calcRoot(x) == calcRoot(y);
  }

  inline int calcSize(int x) {
    return -p_[calcRoot(x)];
  }

private:
  vector<int> p_;
}; // class DisjointSet
} // namespace cs

namespace ts {

template<typename G>
class LCAoffline {
public:
  inline void calc(
      const G& tree,
      const vector<int>& xs,
      const vector<int>& ys,
      vector<int>& lcas) {

    tree_ = &tree;
    xs_ = &xs;
    ys_ = &ys;
    lcas_ = &lcas;
    int n = tree.n();
    dset_.init(n);
    ancestor_.resize(n); FOR(i, 0, n) ancestor_[i] = i;
    black_.resize(n); fill(black_.begin(), black_.end(), false);
    int m = SIZE(xs);
    qIdx_.init(n, m << 1);
    FOR(i, 0, m) {
      qIdx_.add(xs[i], i + 1);
      qIdx_.add(ys[i], -i - 1);
    }
    lcas.resize(m);
    dfs_(0, -1);
  }

private:
  const G* tree_;
  const vector<int>* xs_;
  const vector<int>* ys_;
  vector<int>* lcas_;

  cs::DisjointSet dset_;
  cs::Vector2D<int> qIdx_;
  vector<int> ancestor_;
  vector<bool> black_;

  inline void dfs_(int u, int parent) {
    for (int edgeIdx = tree_->lastOut(u); edgeIdx >= 0; edgeIdx = tree_->nxtOut(edgeIdx)) {
      int v = tree_->toIdx(edgeIdx);
      if (v == parent) continue;
      dfs_(v, u);
      dset_.setFriend(u, v);
      ancestor_[dset_.calcRoot(u)] = u;
    }
    black_[u] = true;
    for (int i = qIdx_.lastOut(u); i >= 0; i = qIdx_.nxtOut(i)) {
      int qIdx = qIdx_.value(i);
      int v = qIdx > 0 ? ys_->at(qIdx - 1) : xs_->at(-qIdx - 1);
      if (black_[v]) lcas_->at(abs(qIdx) - 1) = ancestor_[dset_.calcRoot(v)];
    }
  }
}; // class LCAoffline
} // namespace ts

int n;
gs::UnweightedGraph tree;
vector<int> xs, ys, lcas;
ts::LCAoffline<gs::UnweightedGraph> lca;

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d", &n);
    tree.init(n);
    FOR(i, 0, n) {
      int m; scanf("%d", &m);
      FOR(_, 0, m) {
        int j; scanf("%d", &j);
        tree.addUndirected(i, j - 1);
      }
    }
    int m; scanf("%d", &m);
    xs.resize(m);
    ys.resize(m);
    FOR(i, 0, m) {
      int x, y; scanf("%d%d", &x, &y);
      xs[i] = x - 1;
      ys[i] = y - 1;
    }
    lca.calc(tree, xs, ys, lcas);
    printf("Case %d:\n", taskIdx);
    for (int x : lcas) printf("%d\n", x + 1);
  }
  return 0;
}
