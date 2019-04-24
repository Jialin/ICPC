namespace gs {

class UnweightedSimpleGraph {
public:
  int n;
  vector<vector<bool>> adj;
  vector<int> outDegree;

  inline void init(int _n) {
    n = _n;
    adj.resize(n);
    for (auto& v : adj) {
      v.resize(n);
      fill(v.begin(), v.end(), false);
    }
    outDegree.resize(n);
    fill(outDegree.begin(), outDegree.end(), 0);
  }

  inline void addDirected(int x, int y) {
    if (!adj[x][y]) {
      adj[x][y] = true;
      ++outDegree[x];
    }
  }

  inline void addUndirected(int x, int y) {
    addDirected(x, y);
    addDirected(y, x);
  }
}; // namespace UnweightedSimpleGraph
} // namespace gs
