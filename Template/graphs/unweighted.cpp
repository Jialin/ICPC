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

