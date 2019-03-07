namespace gs { namespace connect {

class ConnectivitySolver {
  vector<bool> visited;
  vector<int> depth, low, parent;

  template<typename G>
  inline void tarjanCutVertex(int u, int _depth, const G& graph, vector<int>& cutVertices) {
    visited[u] = true;
    depth[u] = _depth;
    low[u] = _depth;
    int childCnt = 0;
    bool isCut = false;
    for (int edgeIdx = graph.lastOut[u]; edgeIdx >= 0; edgeIdx = graph.nxtOut[edgeIdx]) {
      int v = graph.toIdx[edgeIdx];
      if (!visited[v]) {
        parent[v] = u;
        tarjanCutVertex(v, _depth + 1, graph, cutVertices);
        ++childCnt;
        if (low[v] >= depth[u]) isCut = true;
        low[u] = min(low[u], low[v]);
      } else if (v != parent[u]) {
        low[u] = min(low[u], depth[v]);
      }
    }
    if ((parent[u] >= 0 && isCut) || (parent[u] < 0 && childCnt > 1)) {
      cutVertices.push_back(u);
    }
  }

public:
  template<typename G>
  inline void cutVertex(const G& graph, vector<int>& cutVertices) {
    int n = graph.n;
    visited.resize(n); fill(visited.begin(), visited.end(), false);
    depth.resize(n);
    low.resize(n);
    parent.resize(n); fill(parent.begin(), parent.end(), -1);
    tarjanCutVertex(0, 0, graph, cutVertices);
  }
};
}} // namespace gs::connect
