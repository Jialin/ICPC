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
    lastOut_.resize(n); FILL(lastOut_, -1);
    inDegree_.resize(n); FILL(inDegree_, 0);
    outDegree_.resize(n); FILL(outDegree_, 0);
    nxtOut_.clear();
    toIdx_.clear();
  }

  inline void addDirected(int x, int y) {
    int edgeIdx = SIZE(nxtOut_);
    nxtOut_.push_back(lastOut_[x]);
    toIdx_.push_back(y);
    lastOut_[x] = edgeIdx;
    ++inDegree_[y];
    ++outDegree_[x];
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
  inline int outDegree(int x) const { return outDegree_[x]; }

private:
  int n_;
  vector<int> lastOut_, nxtOut_, toIdx_, inDegree_, outDegree_;
}; // class UnweightedGraph
} // namespace gs

using gs::UnweightedGraph;

/***********************************************************************************************************************
 * TESTING
 **********************************************************************************************************************/
namespace testing {

string toDisplay(const UnweightedGraph& g) {
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

int n;
unordered_map<string, int> idxLookup;
vector<string> words;
UnweightedGraph g;
SccSolver<UnweightedGraph> sccSolver;
TopologicalSorter<UnweightedGraph> tsorter;
vector<string> answers;
vector<bool> toInclude;

char token[32], c;

inline int getIdx(const string& word) {
  auto it = idxLookup.find(word);
  if (it == idxLookup.end()) {
    idxLookup[word] = SIZE(idxLookup);
    words.push_back(word);
    return SIZE(words) - 1;
  }
  return it->second;
}

int main() {
  while (scanf("%d", &n) != EOF && n) {
    idxLookup.clear();
    words.clear();
    g.init(n);
    FOR(_, 0, n) {
      bool first = true;
      int i = -1;
      while (scanf("%s%c", token, &c) != EOF) {
        int j = getIdx(token);
        if (first) {
          i = j;
          first = false;
        } else {
          g.addDirected(i, j);
        }
        if (c == '\n') break;
      }
    }
    sccSolver.calc(g, true);
    auto& sccGraph = sccSolver.sccGraph();
    tsorter.calc(sccGraph);
    int compCnt = sccGraph.n();
    toInclude.resize(compCnt);
    FOR(i, 0, compCnt) toInclude[i] = sccSolver.compSize(i) > 1;
    for (int u : tsorter.order()) if (toInclude[u]) {
      for (int edgeIdx = sccGraph.lastOut(u); edgeIdx >= 0; edgeIdx = sccGraph.nxtOut(edgeIdx)) {
        toInclude[sccGraph.toIdx(edgeIdx)] = true;
      }
    }
    answers.clear();
    FOR(i, 0, n) if (toInclude[sccSolver.compIdx(i)]) {
      answers.push_back(words[i]);
    }
    SORT(answers);
    printf("%d\n", SIZE(answers));
    bool first = true;
    for (const auto& answer : answers) {
      if (!first) putchar(' ');
      first = false;
      printf("%s", answer.c_str());
    }
    putchar('\n');
  }
  return 0;
}
