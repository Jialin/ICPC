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

#define FOR(i,l,r) for(int i=(l);i<(r);++i)

namespace gs { namespace graph {

template<typename W>
class EdgeWeightedGraph {
public:
  int n;
  vector<int> lastOut;

  vector<int> nxtOut, toIdx;
  vector<W> weights;

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

namespace gs { namespace ff {
template<typename W, typename G>
class FloodFillSolver {
  priority_queue<pair<W, int>, vector<pair<W, int>>, greater<pair<W, int>>> heap;

public:
  inline void calc(G graph, int startIdx, vector<bool>& visited, vector<int>& distances) {
    int n = graph.n;
    for ( ; !heap.empty(); heap.pop()) {}
    visited.resize(n);
    fill(visited.begin(), visited.end(), false);
    distances.resize(n);
    visited[startIdx] = true;
    distances[startIdx] = 0;
    for (heap.push(make_pair(0, startIdx)); !heap.empty(); ) {
      int u = heap.top().second;
      W w = heap.top().first;
      heap.pop();
      if (distances[u] < w) continue;
      for (int edgeIdx = graph.lastOut[u]; edgeIdx >= 0; edgeIdx = graph.nxtOut[edgeIdx]) {
        int v = graph.toIdx[edgeIdx];
        const W& newW = w + graph.weights[edgeIdx];
        if (!visited[v] || newW < distances[v]) {
          visited[v] = true;
          distances[v] = newW;
          heap.push(make_pair(newW, v));
        }
      }
    }
  }
}; // class FloodFillSolver
}} // namespace gs:ff

gs::graph::EdgeWeightedGraph<int> graph;
vector<bool> visited;
vector<int> distances;
gs::ff::FloodFillSolver<int, gs::graph::EdgeWeightedGraph<int>> solver;

int main() {
  graph.init(501);
  int m; scanf("%d", &m);
  FOR(i, 0, m) {
    int x, y, w; scanf("%d%d%d", &x, &y, &w);
    graph.addUndirected(x, y, w);
  }
  int startIdx; scanf("%d", &startIdx);
  solver.calc(graph, startIdx, visited, distances);
  int q; scanf("%d", &q);
  FOR(i, 0, q) {
    int u; scanf("%d", &u);
    if (visited[u]) {
      printf("%d\n", distances[u]);
    } else {
      puts("NO PATH");
    }
  }
  return 0;
}
