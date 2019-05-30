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
