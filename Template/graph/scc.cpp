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
