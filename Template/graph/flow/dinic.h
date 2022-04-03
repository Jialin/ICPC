// !macro_gen
// ALL DINIC_ALL
#pragma once

#include "graph/forward_star/forward_star_macros.h"

#include "debug/debug_basic.h" // TODO: remove

using namespace std;

namespace graph {

template<typename FLOW>
struct Dinic {
#ifdef DINIC_RESERVE // ^
  inline void reserve(int n, int m) {
    int m2 = m << 1;
    lastOut.reserve(n);
    nxtOut.reserve(m2);
    toIdx.reserve(m2);
    flows.reverse(m2);
    caps.reverse(m2);
  }
#endif

  inline void init(int n) {
    lastOut.assign(n, -1);
    nxtOut.clear();
    toIdx.clear();
    flows.clear();
    caps.clear();
  }

  inline void _addEdge(int x, int y, const FLOW& cap) {
    nxtOut.push_back(lastOut[x]);
    toIdx.push_back(y);
    caps.push_back(cap);
    flows.push_back(0);
    lastOut[x] = toIdx.size() - 1;
  }

  inline void addEdge(int x, int y, const FLOW& cap) {
    _addEdge(x, y, cap);
    _addEdge(y, x, 0);
  }

#ifdef DINIC_FLOW // ^
  queue<int> _q;
  vector<int> _levels;

  inline bool _bfs(int sink) {
    while (!_q.empty()) {
      int u = _q.front();
      _q.pop();
      for (int i = lastOut[u]; i >= 0; i = nxtOut[i]) {
        if (flows[i] >= caps[i]) {
          continue;
        }
        int v = toIdx[i];
        if (_levels[v] >= 0) {
          continue;
        }
        _levels[v] = _levels[u] + 1;
        _q.push(v);
      }
    }
    return _levels[sink] >= 0;
  }

  vector<int> _pnts;

  template<typename RETURN>
  inline RETURN _dfs(int u, const RETURN& pushFlow, int sink) {
    // DEBUGV2(u, pushFlow);
    if (!pushFlow) {
      return 0;
    }
    if (u == sink) {
      return pushFlow;
    }
    for (auto& i = _pnts[u]; i >= 0; i = nxtOut[i]) {
      int v = toIdx[i];
      if (_levels[u] + 1 != _levels[v] || flows[i] >= caps[i]) {
        continue;
      }
      auto actualFlow = _dfs(v, min(pushFlow, caps[i] - flows[i]), sink);
      if (!actualFlow) {
        continue;
      }
      // DEBUGV3("+", i, actualFlow);
      flows[i] += actualFlow;
      flows[i ^ 1] -= actualFlow;
      return actualFlow;
    }
    return 0;
  }

  template<typename RETURN>
  inline RETURN calcFlow(int source, int sink) {
    RETURN res = 0;
    _levels.resize(lastOut.size());
    _pnts.resize(lastOut.size());
    while (true) {
      fill(ALL(_levels), -1);
      _levels[source] = 0;
      _q.push(source);
      if (!_bfs(sink)) {
        break;
      }
      _pnts = lastOut;
      while (true) {
        RETURN subRes = _dfs(source, numeric_limits<RETURN>::max(), sink);
        if (!subRes) {
          break;
        }
        res += subRes;
      }
    }
    return res;
  }
#endif

  vector<int> lastOut, nxtOut, toIdx;
  vector<FLOW> flows, caps;
};

} // namespace graph
