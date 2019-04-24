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

namespace gs {

namespace {
  inline static bool isCycle(const gs::UnweightedSimpleGraph& g, const vector<int>& cycle) {
    for (int i = 0, j = 1; i < g.n; ++i) {
      if (!g.adj[cycle[i]][cycle[j]]) return false;
      ++j; if (j == g.n) j = 0;
    }
    return true;
  }
} // namespace

// Ore's Theorem
class Ore {
public:
  // Whether the graph satistifies all conditions in Ore's theorem
  inline static bool isValid(const gs::UnweightedSimpleGraph& g) {
    if (g.n < 3) return false;
    for (int i = 0; i < g.n; ++i) for (int j = i + 1; j < g.n; ++j) {
      if (!g.adj[i][j] && g.outDegree[i] + g.outDegree[j] < g.n) return false;
    }
    return true;
  }

  // Constructs a Hamiltonian cycle
  inline static void construct(const gs::UnweightedSimpleGraph& g, vector<int>& cycle) {
    cycle.resize(g.n);
    for (int i = 0; i < g.n; ++i) cycle[i] = i;
    while (!isCycle(g, cycle)) {
      for (int i = 0; i < g.n; ++i) {
        int i1 = i == g.n - 1 ? 0 : i + 1;
        if (g.adj[cycle[i]][cycle[i1]]) continue;
        for (int j = 0; j < g.n; ++j) {
          int j1 = j == g.n - 1 ? 0 : j + 1;
          if (i == j || i == j1 || i1 == j || i1 == j1) continue;
          if (!g.adj[cycle[i]][cycle[j]] || !g.adj[cycle[i1]][j1]) continue;
          if (i1 < j) {
            reverse(cycle.begin() + i1, cycle.begin() + j + 1);
          } else {
            reverse(cycle.begin() + j1, cycle.begin() + i + 1);
          }
        }
      }
    }
  }
}; // class Ore
} // namespace gs
