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
