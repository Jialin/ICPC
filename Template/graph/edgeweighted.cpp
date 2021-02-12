namespace gs {

template<typename W>
class EdgeWeightedGraph {
public:
  int n;
  vector<int> lastOut, outDegree;

  vector<int> nxtOut, fromIdx, toIdx;
  vector<W> weights;

  inline int edgeCnt() {
    return static_cast<int>(toIdx.size());
  }

  inline void init(int _n) {
    this->n = _n;
    lastOut.resize(n); fill(lastOut.begin(), lastOut.end(), -1);
    outDegree.resize(n); fill(outDegree.begin(), outDegree.end(), 0);
    nxtOut.clear();
    fromIdx.clear();
    toIdx.clear();
    weights.clear();
  }

  inline void addDirected(int x, int y, const W& w) {
    int edgeIdx = static_cast<int>(nxtOut.size());
    nxtOut.push_back(lastOut[x]);
    fromIdx.push_back(x);
    toIdx.push_back(y);
    weights.push_back(w);
    lastOut[x] = edgeIdx;
    ++outDegree[x];
  }

  inline void addUndirected(int x, int y, const W& w) {
    addDirected(x, y, w);
    addDirected(y, x, w);
  }

  inline string toDisplay() {
    ostringstream ss;
    for (int u = 0; u < n; ++u) {
      ss << u << ':';
      for (int edgeIdx = lastOut[u]; edgeIdx >= 0; edgeIdx = nxtOut[edgeIdx]) {
        ss << ' ' << toIdx[edgeIdx];
      }
      ss << endl;
    }
    return ss.str();
  }
}; // class EdgeWeightedGraph
} // namespace gs

namespace testing {

template<typename W>
string toDisplay(gs::EdgeWeightedGraph<W> graph) {
  ostringstream ss;
  for (int u = 0; u < graph.n; ++u) {
    ss << u << ':';
    for (int edgeIdx = graph.lastOut[u]; edgeIdx >= 0; edgeIdx = graph.nxtOut[edgeIdx]) {
      ss << ' ' << graph.toIdx[edgeIdx];
    }
    ss << endl;
  }
  return ss.str();
}
} // namespace testing

