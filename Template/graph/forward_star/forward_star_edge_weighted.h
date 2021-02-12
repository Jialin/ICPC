// !macro_gen
// ALL FORWARD_STAR_EDGE_WEIGHTED_ALL
#pragma once

#include "graph/forward_star/forward_star_edge_weighted_macros.h"
#include "graph/forward_star/forward_star_macros.h" // INCLUDE

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

  vector<EDGE_W> weights;
};

} // namespace graph
