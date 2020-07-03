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
#define CLEAR(vs,v) fill(ALL(vs), v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) (CAST<int>(lower_bound(ALL(v),x)-BEGIN(v)))
#define FOR(i,l,r) for(int i=(l);i<(r);++i)

#define FLUSH fflush(stdout)
#define ERR(...) fprintf(stderr, __VA_ARGS__)

namespace gs {

class UnweightedGraph {
public:
  inline void init(int n) {
    n_ = n;
    lastOut_.resize(n); CLEAR(lastOut_, -1);
    inDegree_.resize(n); CLEAR(inDegree_, 0);
    nxtOut_.clear();
    toIdx_.clear();
  }

  inline void addDirected(int x, int y) {
    int edgeIdx = SIZE(nxtOut_);
    nxtOut_.push_back(lastOut_[x]);
    toIdx_.push_back(y);
    lastOut_[x] = edgeIdx;
    ++inDegree_[y];
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
  inline int inDegree(int x) const { return inDegree_[x]; }

private:
  int n_;
  vector<int> lastOut_, nxtOut_, toIdx_, inDegree_;
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

namespace gs {

template<typename G>
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

  inline int compCnt() const { return compCnt_; }
  inline int compIdx(int u) const { return compIdx_[u]; }
  inline const UnweightedGraph& sccGraph() const { return sccG_; }

private:
  inline int calc_(bool buildSccTree) {
    int n = g_->n();
    compIdx_.resize(n);
    if (sccProcessor_) scc_.reserve(n);
    dfn_.resize(n); CLEAR(dfn_, -1);
    low_.resize(n); CLEAR(low_, -1);
    in_.resize(n); CLEAR(in_, false);
    compCnt_ = 0;
    tag_ = 0;
    FOR(i, 0, n) if (dfn_[i] < 0) {
      stack_.clear();
      tarjan_(i);
    }
    if (buildSccTree) {
      sccG_.init(compCnt_);
      FOR(u, 0, n) {
        int uCompIdx = compIdx_[u];
        for (int edgeIdx = g_->lastOut(u); edgeIdx >= 0; edgeIdx = g_->nxtOut(edgeIdx)) {
          int vCompIdx = compIdx_[g_->toIdx(edgeIdx)];
          if (uCompIdx != vCompIdx) sccG_.addDirected(uCompIdx, vCompIdx);
        }
      }
    }
    return compCnt_;
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
      int v;
      scc_.clear();
      do {
        v = stack_.back();
        stack_.pop_back();
        in_[v] = false;
        compIdx_[v] = compCnt_;
        if (sccProcessor_) scc_.push_back(v);
      } while (u != v);
      if (sccProcessor_) {
        reverse(ALL(scc_));
        (*sccProcessor_)(compCnt_, scc_);
      }
      ++compCnt_;
    }
  }

  const G* g_;
  const function<void(int, const vector<int>&)>* sccProcessor_;
  int compCnt_, tag_;
  vector<int> compIdx_;
  vector<int> dfn_, low_;
  vector<bool> in_;
  vector<int> stack_;
  vector<int> scc_;
  UnweightedGraph sccG_;
}; // class SccSolver
} // namespace gs

int n, m;
gs::UnweightedGraph g;
gs::SccSolver<gs::UnweightedGraph> sccSolver;

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    scanf("%d%d", &n, &m);
    g.init(n);
    FOR(i, 0, m) {
      int x, y; scanf("%d%d", &x, &y);
      g.addDirected(x - 1, y - 1);
    }
    int compCnt = sccSolver.calc(g, true);
    auto& sccG = sccSolver.sccGraph();
    int res = 0;
    FOR(i, 0, compCnt) res += !sccG.inDegree(i);
    printf("%d\n", res);
  }
  return 0;
}
