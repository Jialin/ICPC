#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define SIZE(v) (static_cast<int>((v).size()))

#define FOR(i,l,r) for(int i=(l);i<(r);++i)

namespace gs { namespace graph {

class UnweightedGraph {
public:
  int n;
  vector<int> lastOut;

  vector<int> nxtOut, toIdx;

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
};
}} // namespace gs::graph

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

gs::graph::UnweightedGraph graph;
vector<int> vertices;
gs::connect::ConnectivitySolver solver;

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) != EOF && n > 0) {
    graph.init(n);
    FOR(i, 0, m) {
      int x, y; scanf("%d%d", &x, &y);
      graph.addUndirected(x - 1, y - 1);
    }
    vertices.clear();
    solver.cutVertex(graph, vertices);
    printf("%d\n", SIZE(vertices));
  }
  return 0;
}
