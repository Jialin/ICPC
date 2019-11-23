namespace graphs {

class UnweightedGraph {
public:
  inline void init(int n_, int m = -1) {
    this->n = n_;
    lastOut.assign(n, -1);
    inDegree.assign(n, 0);
    outDegree.assign(n, 0);
    if (m >= 0) {
      nxtOut.reserve(m);
      toIdx.reserve(m);
    }
    nxtOut.clear();
    toIdx.clear();
  }

  inline void addDirected(int u, int v) {
    int edgeIdx = edgeCnt();
    nxtOut.push_back(lastOut[u]);
    toIdx.push_back(v);
    lastOut[u] = edgeIdx;
    ++inDegree[v];
    ++outDegree[u];
  }

  inline void addUndirected(int u, int v) {
    addDirected(u, v);
    addDirected(v, u);
  }

  inline void outEdges(int u,
                       const function<void(int)> &edgeIdxProcessor) const {
    for (int edgeIdx = lastOut[u]; edgeIdx >= 0; edgeIdx = nxtOut[edgeIdx]) {
      edgeIdxProcessor(edgeIdx);
    }
  }

  inline int edgeCnt() const { return static_cast<int>(toIdx.size()); }

  int n;
  vector<int> lastOut, inDegree, outDegree;
  vector<int> nxtOut, toIdx;
};

} // namespace graphs

/*******************************************************************************
Example usage:
  for (int edgeIdx = g.lastOut[u]; edgeIdx >= 0; edgeIdx = g.nxtOut[edgeIdx]) {}
  g.outEdges(u, [&](int edgeIdx) {});
 ******************************************************************************/

/*******************************************************************************
 * TESTING
 ******************************************************************************/
namespace testing {

string toDisplay(const graphs::UnweightedGraph &g) {
  ostringstream ss;
  for (int i = 0; i < g.n; ++i) {
    ss << i << " to ";
    g.outEdges(i, [&ss, &g](int edgeIdx) { ss << g.toIdx(edgeIdx) << ","; });
    ss << endl;
  }
  return ss.str();
}
} // namespace testing
