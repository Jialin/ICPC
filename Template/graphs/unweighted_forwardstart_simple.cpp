namespace graphs {

class UnweightedGraphForwardStarSimple {
public:
  inline void init(int n, int m = -1) {
    n_ = n;
    lastOut_.resize(n);
    FILL(lastOut_, -1);
    nxtOut_.clear();
    toIdx_.clear();
    if (m >= 0) {
      nxtOut_.reserve(m);
      toIdx_.reserve(m);
    }
  }

  inline void addDirected(int u, int v) {
    int edgeIdx = SIZE(nxtOut_);
    nxtOut_.push_back(lastOut_[u]);
    toIdx_.push_back(v);
    lastOut_[u] = edgeIdx;
  }

  inline void addUndirected(int u, int v) {
    addDirected(u, v);
    addDirected(v, u);
  }

  inline int nodeCnt() const { return n_; }
  inline int edgeCnt() const { return SIZE(toIdx_); }
  inline int lastOut(int u) const { return lastOut_[u]; }
  inline int nxtOut(int u) const { return nxtOut_[u]; }
  inline int toIdx(int u) const { return toIdx_[u]; }

private:
  int n_;
  vector<int> lastOut_;
  vector<int> nxtOut_;
  vector<int> toIdx_;
}; // class UnweightedGraphForwardStarSimple

} // namespace graphs

/*******************************************************************************
Example usage:
  for (int edgeIdx = graph.lastOut(u); edgeIdx >= 0;
       edgeIdx = graph.nxtOut(edgeIdx))
 ******************************************************************************/
