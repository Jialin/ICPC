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
