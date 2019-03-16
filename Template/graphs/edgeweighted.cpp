namespace gs { namespace graph {

template<typename W>
class EdgeWeightedGraph {
public:
  int n;
  vector<int> lastOut;

  vector<int> nxtOut, toIdx;
  vector<W> weights;

  inline int edgeCnt() {
    return static_cast<int>(toIdx.size());
  }

  inline void init(int _n) {
    this->n = _n;
    lastOut.resize(n);
    fill(lastOut.begin(), lastOut.end(), -1);
    nxtOut.clear();
    toIdx.clear();
    weights.clear();
  }

  inline void addDirected(int x, int y, const W& w) {
    int edgeIdx = static_cast<int>(nxtOut.size());
    nxtOut.push_back(lastOut[x]);
    toIdx.push_back(y);
    weights.push_back(w);
    lastOut[x] = edgeIdx;
  }

  inline void addUndirected(int x, int y, const W& w) {
    addDirected(x, y, w);
    addDirected(y, x, w);
  }
}; // class EdgeWeightedGraph
}} // namespace gs::graph
