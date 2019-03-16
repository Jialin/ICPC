namespace gs { namespace graph {

class UnweightedGraph {
public:
  int n;
  vector<int> lastOut;

  vector<int> nxtOut, toIdx;

  inline int edgeCnt() {
    return static_cast<int>(toIdx.size());
  }

  inline void init(int _n) {
    this->n = _n;
    lastOut.resize(n);
    fill(lastOut.begin(), lastOut.end(), -1);
    nxtOut.clear();
    toIdx.clear();
  }

  inline void addDirected(int x, int y) {
    int edgeIdx = static_cast<int>(nxtOut.size());
    nxtOut.push_back(lastOut[x]);
    toIdx.push_back(y);
    lastOut[x] = edgeIdx;
  }

  inline void addUndirected(int x, int y) {
    addDirected(x, y);
    addDirected(y, x);
  }
}; // class UnweightedGraph
}} // namespace gs::graph
