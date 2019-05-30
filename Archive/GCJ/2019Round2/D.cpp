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
#define FILL(vs,v) fill(ALL(vs), v)
#define CLEAR(q) for (;!q.empty();q.pop())
#define UNIQUE(v) sort(ALL(v));(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) (CAST<int>(lower_bound(ALL(v),x)-BEGIN(v)))
#define FOR(i,l,r) for(int i=(l);i<(r);++i)

#define FLUSH fflush(stdout)
#define ERR(...) fprintf(stderr, __VA_ARGS__)

namespace gs {

class UnweightedGraph {
public:
  inline void init(int n) {
    n_ = n;
    lastOut_.resize(n); FILL(lastOut_, -1);
    inDegree_.resize(n); FILL(inDegree_, 0);
    outDegree_.resize(n); FILL(outDegree_, 0);
    nxtOut_.clear();
    toIdx_.clear();
  }

  inline void addDirected(int u, int v) {
    int edgeIdx = SIZE(nxtOut_);
    nxtOut_.push_back(lastOut_[u]);
    toIdx_.push_back(v);
    lastOut_[u] = edgeIdx;
    ++inDegree_[v];
    ++outDegree_[u];
  }

  inline void addUndirected(int u, int v) {
    addDirected(u, v);
    addDirected(v, u);
  }

  inline void outEdges(int u, const function<void(int)>& edgeIdxProcessor) const {
    for (int edgeIdx = lastOut_[u]; edgeIdx >= 0; edgeIdx = nxtOut_[edgeIdx]) edgeIdxProcessor(edgeIdx);
  }

  inline int n() const { return n_; }
  inline int edgeCnt() const { return SIZE(toIdx_); }
  inline int lastOut(int u) const { return lastOut_[u]; }
  inline int nxtOut(int u) const { return nxtOut_[u]; }
  inline int toIdx(int u) const { return toIdx_[u]; }
  inline int inDegree(int u) const { return inDegree_[u]; }
  inline int outDegree(int u) const { return outDegree_[u]; }

private:
  int n_;
  vector<int> lastOut_, nxtOut_, toIdx_, inDegree_, outDegree_;
}; // class UnweightedGraph
} // namespace gs

using gs::UnweightedGraph;

namespace gs {

template<typename G = UnweightedGraph>
class SccSolver {
public:
  inline int calc(const G& g, bool buildSccTree = false) {
    g_ = &g;
    sccProcessor_ = nullptr;
    return calc_(buildSccTree);
  }

  inline int calc(const G& g, const function<void(int, const vector<int>&)>& sccProcessor, bool buildSccTree = false) {
    g_ = &g;
    sccProcessor_ = &sccProcessor;
    return calc_(buildSccTree);
  }

  inline int compCnt() const { return SIZE(compSize_); }
  inline int compIdx(int u) const { return compIdx_[u]; }
  inline int compSize(int i) const { return compSize_[i]; }
  inline const UnweightedGraph& sccGraph() const { return sccG_; }

private:
  inline int calc_(bool buildSccTree) {
    int n = g_->n();
    compIdx_.resize(n);
    compSize_.clear();
    if (sccProcessor_) scc_.reserve(n);
    dfn_.resize(n); FILL(dfn_, -1);
    low_.resize(n); FILL(low_, -1);
    in_.resize(n); FILL(in_, false);
    tag_ = 0;
    FOR(i, 0, n) if (dfn_[i] < 0) {
      stack_.clear();
      tarjan_(i);
    }
    if (buildSccTree) {
      sccG_.init(compCnt());
      FOR(u, 0, n) {
        int uCompIdx = compIdx_[u];
        for (int edgeIdx = g_->lastOut(u); edgeIdx >= 0; edgeIdx = g_->nxtOut(edgeIdx)) {
          int vCompIdx = compIdx_[g_->toIdx(edgeIdx)];
          if (uCompIdx != vCompIdx) sccG_.addDirected(uCompIdx, vCompIdx);
        }
      }
    }
    return compCnt();
  }

  inline void tarjan_(int u) {
    stack_.push_back(u);
    in_[u] = true;
    dfn_[u] = low_[u] = tag_++;
    for (int edgeIdx = g_->lastOut(u); edgeIdx >= 0; edgeIdx = g_->nxtOut(edgeIdx)) {
      int v = g_->toIdx(edgeIdx);
      if (dfn_[v] < 0) {
        tarjan_(v);
        low_[u] = min(low_[u], low_[v]);
      } else if (in_[v]) {
        low_[u] = min(low_[u], dfn_[v]);
      }
    }
    if (dfn_[u] == low_[u]) {
      int cnt = 0;
      int v;
      scc_.clear();
      do {
        v = stack_.back();
        stack_.pop_back();
        in_[v] = false;
        compIdx_[v] = compCnt();
        if (sccProcessor_) scc_.push_back(v);
        ++cnt;
      } while (u != v);
      if (sccProcessor_) {
        reverse(ALL(scc_));
        (*sccProcessor_)(compCnt(), scc_);
      }
      compSize_.push_back(cnt);
    }
  }

  const G* g_;
  const function<void(int, const vector<int>&)>* sccProcessor_;
  int tag_;
  vector<int> compIdx_, compSize_, dfn_, low_, stack_, scc_;
  vector<bool> in_;
  UnweightedGraph sccG_;
}; // class SccSolver
} // namespace gs

using gs::SccSolver;

namespace gs {

template<typename G>
class TopologicalSorter {
public:
  inline void calc(const G& g) {
    int n = g.n();
    order_.clear();
    inDegree_.resize(n);
    CLEAR(q_);
    FOR(i, 0, n) {
      inDegree_[i] = g.inDegree(i);
      if (!inDegree_[i]) q_.push(i);
    }
    for ( ; !q_.empty(); q_.pop()) {
      int u = q_.front();
      order_.push_back(u);
      for (int edgeIdx = g.lastOut(u); edgeIdx >= 0; edgeIdx = g.nxtOut(edgeIdx)) {
        int v = g.toIdx(edgeIdx);
        --inDegree_[v];
        if (!inDegree_[v]) q_.push(v);
      }
    }
  }

  inline const vector<int>& order() const { return order_; }

private:
  vector<int> order_, inDegree_;
  queue<int> q_;
};
} // namespace gs

using gs::TopologicalSorter;

/******************
 * TO BE VERIFIED.
 ******************/
namespace math {

inline int extGcd(int a, int b, int& x0, int& x1) {
  if (!b) {
    x0 = 1;
    x1 = 0;
    return a;
  }
  int gcd = extGcd(b, a % b, x0, x1);
  swap(x0, x1);
  x1 -= a / b * x0;
  return gcd;
}
} // namespace math

namespace math {

namespace {

inline int slightFix_(int a, int mod) {
  return a >= mod
      ? a - mod
      : a < 0 ? a + mod : a;
}

inline int fix_(int a, int mod) {
  a = slightFix_(a, mod);
  return 0 <= a && a < mod ? a : slightFix_(a % mod, mod);
}

inline int add_(int a, int b, int mod) {
  return fix_(a + b, mod);
}

inline int mul_(int a, int b, int mod) {
  a = fix_(a, mod);
  b = fix_(b, mod);
  return !a
      ? 0
      : b < mod / a ? a * b : static_cast<LL>(a) * b % mod;
}

inline int inv_(int a, int mod, int& x0, int& x1) {
  assert(extGcd(a, mod, x0, x1) == 1);
  return slightFix_(x0, mod);
}

} // namespace

class ModInt {
public:
  inline ModInt(int mod = 1000000007) : mod_(mod) {}

  inline int inv(int a) { return inv_(a, mod_, x0_, x1_); }
  inline int add(int a, int b) { return add_(a, b, mod_); }
  inline int mul(int a, int b) { return mul_(a, b, mod_); }
  inline int div(int a, int b) { return mul_(a, inv(b), mod_); }
private:
  int mod_;
  int x0_, x1_;
}; // class ModInt
} // namespace math

using math::ModInt;

int n;
UnweightedGraph g;
SccSolver<UnweightedGraph> sccSolver;
TopologicalSorter<UnweightedGraph> topSorter;
vector<int> xs, ys, weights;
vector<bool> unbounded, anyWeight, infiniteLoop;
vector<vector<int>> comps;
ModInt mod;

inline bool calcUnbounded() {
  const auto& sccG = sccSolver.sccGraph();
  int m = sccG.n();
  unbounded.resize(m); FILL(unbounded, false);
  anyWeight.resize(m); FILL(anyWeight, false);
  infiniteLoop.resize(m); FILL(infiniteLoop, false);
  for (int uCompIdx : topSorter.order()) {
    for (int u : comps[uCompIdx]) {
      if (weights[u] > 0) {
        anyWeight[uCompIdx] = true;
        break;
      }
    }
    if (!anyWeight[uCompIdx]) continue;
    if (SIZE(comps[uCompIdx]) > 1) {
      infiniteLoop[uCompIdx] = true;
    } else {
      int u = comps[uCompIdx].front();
      infiniteLoop[uCompIdx] = xs[u] == u || ys[u] == u;
    }
    for (int u : comps[uCompIdx]) {
      if (uCompIdx == sccSolver.compIdx(xs[u]) && uCompIdx == sccSolver.compIdx(ys[u])) {
        unbounded[uCompIdx] = true;
        break;
      }
    }
    sccG.outEdges(uCompIdx, [&](int edgeIdx) {
      int vCompIdx = sccG.toIdx(edgeIdx);
      anyWeight[vCompIdx] = true;
      if (infiniteLoop[uCompIdx] || unbounded[uCompIdx]) unbounded[vCompIdx] = true;
    });
  }
  return unbounded[sccSolver.compIdx(0)];
}

inline void expand(int u) {
  int w = weights[u];
  weights[u] = 0;
  weights[xs[u]] = mod.add(weights[xs[u]], w);
  weights[ys[u]] = mod.add(weights[ys[u]], w);
}

inline int calc() {
  int leadCompIdx = sccSolver.compIdx(0);
  for (int uCompIdx : topSorter.order()) {
    const auto& us = comps[uCompIdx];
    if (uCompIdx == leadCompIdx) {
      int idx = -1;
      FOR(i, 0, SIZE(us)) if (!us[i]) {
        idx = i;
        break;
      }
      FOR(i, idx + 1, SIZE(us)) expand(us[i]);
      FOR(i, 0, idx) expand(us[i]);
      FOR(i, idx + 1, SIZE(us)) expand(us[i]);
      FOR(i, 0, idx) expand(us[i]);
      break;
    }
    for (int u : us) expand(u);
    for (int u : us) expand(u);
  }
  return weights[0];
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d", &n);
    g.init(n);
    xs.resize(n);
    ys.resize(n);
    FOR(i, 0, n) {
      int x, y; scanf("%d%d", &x, &y); --x; --y;
      xs[i] = x;
      ys[i] = y;
      g.addDirected(i, x);
      g.addDirected(i, y);
    }
    weights.resize(n);
    FOR(i, 0, n) scanf("%d", &weights[i]);
    comps.clear(); comps.reserve(n);
    sccSolver.calc(
        g,
        [&](int, const vector<int>& us) { comps.push_back(us); },
        true);
    topSorter.calc(sccSolver.sccGraph());
    printf("Case #%d: ", taskIdx);
    if (calcUnbounded()) {
      puts("UNBOUNDED");
    } else {
      printf("%d\n", calc());
    }
  }
  return 0;
}

