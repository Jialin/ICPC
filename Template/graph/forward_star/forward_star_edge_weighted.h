// !macro_gen
// ALL FORWARD_STAR_EDGE_WEIGHTED_ALL
#pragma once

#include <queue>

#include "graph/forward_star/forward_star_edge_weighted_macros.h"
#include "graph/forward_star/forward_star_macros.h" // INCLUDE

#include "common/macros.h"
#include "debug/debug_basic.h"
#include "graph/forward_star/forward_star.h"

using namespace std;

namespace graph {

template<typename EDGE_W>
struct ForwardStarEdgeWeighted : ForwardStar {
  inline ForwardStarEdgeWeighted(int n = 0, int edgeCapacity = -1) {
    init(n, edgeCapacity);
  }

  inline void init(int n, int edgeCapacity = -1) {
    ForwardStar::init(n, edgeCapacity);
    if (edgeCapacity > 0) {
      weights.reserve(edgeCapacity);
    }
    weights.clear();
  }

  inline void addDirected(int x, int y, EDGE_W&& w) {
    weights.push_back(std::move(w));
    ForwardStar::addDirected(x, y);
  }

#ifdef FORWARD_STAR_EDGE_WEIGHTED_ADD_UNDIRECTED // ^
  inline void addUndirected(int x, int y, EDGE_W&& w) {
    weights.push_back(w);
    weights.push_back(std::move(w));
    // FORWARD_STAR_EDGE_WEIGHTED_ADD_UNDIRECTED => FORWARD_STAR_ADD_UNDIRECTED
    ForwardStar::addUndirected(x, y);
  }
#endif

// NOTE: updater(fromNodeIdx, toNodeIdx, edgeIdx) returns whether distance to <toNodeIdx> is updated
#ifdef FORWARD_STAR_EDGE_WEIGHTED_SPFA // ^
  inline void spfa(int startIdx, const function<bool(int, int, int)>& updater) {
    static vector<bool> inQ;
    static queue<int> q;
    inQ.assign(_n, false);
    q.push(startIdx);
    inQ[startIdx] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inQ[u] = false;
      FOREDGE(i, (*this), u) {
        int v = toIdx[i];
        if (updater(u, v, i) && !inQ[v]) {
          q.push(v);
          inQ[v] = true;
        }
      }
    }
  }
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const ForwardStarEdgeWeighted& g) {
    o << "In total " << g._n << " nodes, " << g._edgeIdx << " edges." << endl;
    FOR(i, 0, g._n) {
      o << "From node " << i << ":" << endl;
      FOREDGE(j, i, g) {
        o << "\t=> node " << g.toIdx[j] << ": " << g.weights[j] << endl;
      }
    }
    return o;
  }
#endif

  vector<EDGE_W> weights;
};

} // namespace graph

#ifdef LOCAL
template<typename EDGE_W>
inline string totype(const graph::ForwardStarEdgeWeighted<EDGE_W>& v) {
  return "ForwardStarEdgeWeighted<" + totype(EDGE_W()) + ">";
}
#endif
