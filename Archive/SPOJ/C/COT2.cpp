#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
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
#include <tuple>
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
#define INDEX(v,x) CAST<int>(lower_bound(ALL(v),x)-BEGIN(v))
#define FOR(i,l,r) for(int i=(l);i<(r);++i)
#define FORBACK(i,l,r) for(int i=(r)-1;i>=(l);--i)

inline char getChar() { return CAST<char>(getchar()); }
inline int getInt() { char ch; while ((ch = getChar()) != EOF && !isdigit(ch) && ch != '+' && ch != '-') {} bool positive = ch == '-' ? false : true; int res = isdigit(ch) ? ch - '0' : 0; for ( ; (ch = getChar()) != EOF && isdigit(ch); res = res * 10 + ch - '0') {} return positive ? res : -res; }

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

namespace testing {

string toDisplay(const gs::UnweightedGraph& g) {
  ostringstream ss;
  FOR(i, 0, g.n()) {
    ss << i << " to ";
    for (int edgeIdx = g.lastOut(i); edgeIdx >= 0; edgeIdx = g.nxtOut(edgeIdx)) {
      ss << g.toIdx(edgeIdx) << ",";
    }
    ss << endl;
  }
  return ss.str();
}
} // namespace testing

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

namespace trees {

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
} // namespace trees

namespace trees {

template<typename G>
class MoSolver {
public:
  inline void calc(
      const G& tree,
      const vector<int>& xs,
      const vector<int>& ys,
      const function<void(int)> nodeAdder,
      const function<void(int)> nodeRemover,
      const function<void(int)> queryIdxProcessor) {

    int n = tree.n();
    tree_ = &tree;
    nodeAdder_ = &nodeAdder;
    nodeRemover_ = &nodeRemover;
    dfs_();
    lca_.calc(tree, xs, ys, lcas_);
    int m = SIZE(xs);
    queries_.resize(m); FOR(i, 0, m) queries_[i] = i;
    int bucket = max(1, CAST<int>(sqrt(n)));
    sort(queries_.begin(), queries_.end(), [&](const int i, const int j) {
      int lx = orders_[xs[i]], rx = orders_[ys[i]]; if (lx > rx) swap(lx, rx);
      int ly = orders_[xs[j]], ry = orders_[ys[j]]; if (ly > ry) swap(ly, ry);
      int bx = lx / bucket, by = ly / bucket;
      if (bx != by) {
        return bx < by;
      } else {
        return (bx & 1) ? rx < ry : rx > ry;
      }
    });
    in_.resize(n); fill(in_.begin(), in_.end(), false);
    int u = 0, v = 0;
    for (int i : queries_) {
      int nxtU = xs[i], nxtV = ys[i]; if (orders_[nxtU] > orders_[nxtV]) swap(nxtU, nxtV);
      flipPath_(u, nxtU);
      flipPath_(v, nxtV);
      u = nxtU;
      v = nxtV;
      int lca = lcas_[i];
      nodeAdder(lca);
      queryIdxProcessor(i);
      nodeRemover(lca);
    }
  }

private:
  const G* tree_;
  const function<void(int)>* nodeAdder_;
  const function<void(int)>* nodeRemover_;

  trees::LCAoffline<gs::UnweightedGraph> lca_;
  int orderTag_;
  vector<int> orders_, lcas_, cnts_, queries_, depths_, parents_;
  vector<bool> in_;

  inline void dfs_() {
    int n = tree_->n();
    depths_.resize(n);
    parents_.resize(n);
    orders_.resize(n);
    orderTag_ = 0;
    dfs_(0, 0, -1);
  }

  inline void dfs_(int depth, int u, int parent) {
    parents_[u] = parent;
    depths_[u] = depth;
    if (depth & 1) orders_[u] = orderTag_++;
    for (int edgeIdx = tree_->lastOut(u); edgeIdx >= 0; edgeIdx = tree_->nxtOut(edgeIdx)) {
      int v = tree_->toIdx(edgeIdx);
      if (v != parent) dfs_(depth + 1, v, u);
    }
    if (!(depth & 1)) orders_[u] = orderTag_++;
  }

  inline void flipPath_(int u, int v) {
    while (u != v) {
      if (depths_[u] >= depths_[v]) {
        flip_(u);
        u = parents_[u];
      } else {
        flip_(v);
        v = parents_[v];
      }
    }
  }

  inline void flip_(int u) {
    if (in_[u]) {
      (*nodeRemover_)(u);
    } else {
      (*nodeAdder_)(u);
    }
    in_[u] = !in_[u];
  }
}; // class MoSolver
} // namespace trees

namespace cs {

/** Add and remove numbers from the counter, the counter will keep track of the number of unqiue numbers. */
class UniqueCounterSimple {
public:
  inline void init(int n) {
    uniqueCnt_ = 0;
    vs_.resize(n);
  }

  inline void update(int x, int v) {
    if (!vs_[x]) ++uniqueCnt_;
    vs_[x] += v;
    if (!vs_[x]) --uniqueCnt_;
  }

  inline int uniqueCnt() const { return uniqueCnt_; }
  inline int v(int x) const { return vs_[x]; }
  inline int n() const { return SIZE(vs_); }

private:
  int uniqueCnt_;
  vector<int> vs_;
}; // class UniqueCounter
} // namespace cs

namespace testing {

string toDisplay(const cs::UniqueCounterSimple& counter) {
  ostringstream ss;
  ss << "vs(" << counter.uniqueCnt() << "):";
  FOR(i, 0, counter.n()) {
    ss << counter.v(i) << ",";
  }
  ss << endl;
  return ss.str();
}
} // namespace testing

int n, m;
vector<int> vs, vDis;
gs::UnweightedGraph tree;
vector<int> xs, ys;
cs::UniqueCounterSimple counter;
vector<int> answers;
trees::MoSolver<gs::UnweightedGraph> moSolver;

int main() {
  n = getInt();
  m = getInt();
  vs.resize(n);
  vDis.resize(n);
  FOR(i, 0, n) {
    vs[i] = getInt();
    vDis[i] = vs[i];
  }
  UNIQUE(vDis);
  FOR(i, 0, n) vs[i] = INDEX(vDis, vs[i]);
  tree.init(n);
  FOR(_, 1, n) {
    int x = getInt();
    int y = getInt();
    tree.addUndirected(x - 1, y - 1);
  }
  xs.resize(m);
  ys.resize(m);
  FOR(i, 0, m) {
    int x = getInt();
    int y = getInt();
    xs[i] = x - 1;
    ys[i] = y - 1;
  }
  counter.init(SIZE(vDis));
  answers.resize(m);
  moSolver.calc(
      tree,
      xs,
      ys,
      [](int i) {
        counter.update(vs[i], 1);
      },
      [](int i) {
        counter.update(vs[i], -1);
      },
      [](int i) {
        answers[i] = counter.uniqueCnt();
      });
  for (int answer : answers) printf("%d\n", answer);
  return 0;
}
