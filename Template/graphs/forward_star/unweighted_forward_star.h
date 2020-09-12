#pragma once

#include <vector>

using namespace std;

namespace graphs {

struct UnweightedForwardStar {
  inline UnweightedForwardStar() {}

  inline UnweightedForwardStar(int n, int edgeCap = -1) {
    init(n, edgeCap);
  }

  inline void init(int n_, int edgeCap = -1) {
    n = n_;
    lastOut.assign(n, -1);
    inDegree.assign(n, 0);
    if (edgeCap > 0) {
      nxtOut.reserve(edgeCap);
      toIdx.reserve(edgeCap);
    }
    nxtOut.clear();
    toIdx.clear();
    _edgeIdx = 0;
  }

  inline void addDirected(int x, int y) {
    nxtOut.push_back(lastOut[x]);
    toIdx.push_back(y);
    lastOut[x] = _edgeIdx++;
    ++inDegree[y];
  }

  inline void addUndirected(int x, int y) {
    addDirected(x, y);
    addDirected(y, x);
  }

  int n;
  vector<int> lastOut, inDegree;
  vector<int> nxtOut, toIdx;

  int _edgeIdx;
};

} // namespace graphs
