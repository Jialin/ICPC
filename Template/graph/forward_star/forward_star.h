// !macro_gen
// ALL FORWARD_STAR_ALL
#pragma once

#include "graph/forward_star/forward_star_macros.h"

using namespace std;

namespace graph {

struct ForwardStar {
  inline ForwardStar(int n = 0, int edgeCapacity = -1) {
    init(n, edgeCapacity);
  }

  inline void init(int n, int edgeCapacity = -1) {
    if (edgeCapacity > 0) {
      nxtOut.reserve(edgeCapacity);
      toIdx.reserve(edgeCapacity);
    }
    _n = n;
    _edgeIdx = 0;
    lastOut.assign(_n, -1);
    nxtOut.clear();
    toIdx.clear();
#ifdef FORWARD_STAR_IN_DEGREE
    inDegree.assign(n, 0);
#endif
  }

  inline void addDirected(int x, int y) {
    nxtOut.push_back(lastOut[x]);
    toIdx.push_back(y);
    lastOut[x] = _edgeIdx++;
#ifdef FORWARD_STAR_IN_DEGREE
    ++inDegree[y];
#endif
  }

#ifdef FORWARD_STAR_ADD_UNDIRECTED // ^
  inline void addUndirected(int x, int y) {
    addDirected(x, y);
    addDirected(y, x);
  }
#endif

  vector<int> lastOut, nxtOut, toIdx;
#ifdef FORWARD_STAR_IN_DEGREE // ^
  vector<int> inDegree;
#endif

#ifdef LOCAL
  friend ostream& operator<<(ostream& o, const ForwardStar& g) {
    o << "In total " << g._n << " nodes, " << g._edgeIdx << " edges." << endl;
    FOR(i, 0, g._n) {
      o << "From node " << i << ":" << endl;
      FOREDGE(j, i, g) {
        o << "\t=> node " << g.toIdx[j] << endl;
      }
    }
    return o;
  }
#endif

  int _n, _edgeIdx;
};

} // namespace graph

#ifdef LOCAL
template<typename EDGE_W>
inline string totype(const graph::ForwardStar& v) {
  return "ForwardStar";
}
#endif
