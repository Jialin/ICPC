#pragma once

#include <functional>
#include <queue>
#include <vector>

using namespace std;

namespace graphs {

struct TopologicalSorter {
  // Returns whether the GRAPH is a DAG
  template<typename GRAPH>
  inline bool calc(const GRAPH& g, const function<void(int)>& processor) {
    for (; !_q.empty(); _q.pop()) {}
    int n = g.n;
    _inDegree.resize(n);
    for (int i = n - 1; i >= 0; --i) {
      _inDegree[i] = g.inDegree[i];
      if (!_inDegree[i]) {
        _q.push(i);
      }
    }
    for (; !_q.empty(); _q.pop()) {
      int u = _q.front();
      processor(u);
      --n;
      for (int edgeIdx = g.lastOut[u]; edgeIdx >= 0;
           edgeIdx = g.nxtOut[edgeIdx]) {
        int v = g.toIdx[edgeIdx];
        --_inDegree[v];
        if (!_inDegree[v]) {
          _q.push(v);
        }
      }
    }
    return !n;
  }

  queue<int> _q;
  vector<int> _inDegree;
};

} // namespace graphs
