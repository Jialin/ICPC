namespace gs {

template<typename W>
class EdgeWeightedGraph {
public:
  int n;
  vector<int> lastOut;

  vector<int> nxtOut, fromIdx, toIdx;
  vector<W> weights;

  inline int edgeCnt() {
    return static_cast<int>(toIdx.size());
  }

  inline void init(int _n) {
    this->n = _n;
    lastOut.resize(n);
    fill(lastOut.begin(), lastOut.end(), -1);
    nxtOut.clear();
    fromIdx.clear();
    toIdx.clear();
    weights.clear();
  }

  inline void addDirected(int x, int y, const W& w) {
    int edgeIdx = static_cast<int>(nxtOut.size());
    nxtOut.push_back(lastOut[x]);
    fromIdx.push_back(x);
    toIdx.push_back(y);
    weights.push_back(w);
    lastOut[x] = edgeIdx;
  }

  inline void addUndirected(int x, int y, const W& w) {
    addDirected(x, y, w);
    addDirected(y, x, w);
  }

  inline string toDisplay() {
    ostringstream ss;
    for (int u = 0; u < n; ++u) {
      ss << u << ':';
      for (int edgeIdx = lastOut[u]; edgeIdx >= 0; edgeIdx = nxtOut[edgeIdx]) {
        ss << ' ' << toIdx[edgeIdx];
      }
      ss << endl;
    }
    return ss.str();
  }
}; // class EdgeWeightedGraph
} // namespace gs

namespace cs {

class DisjointSet {
public:
  vector<int> p;

  inline void init(int n) {
    p.resize(n);
    fill(p.begin(), p.end(), -1);
  }

  inline int calcRoot(int x) {
    int root = x;
    for ( ; p[root] >= 0; root = p[root]) {}
    while (p[x] >= 0) {
      int tmp = p[x];
      p[x] = root;
      x = tmp;
    }
    return root;
  }

  inline bool setFriend(int x, int y) {
    int rootX = calcRoot(x);
    int rootY = calcRoot(y);
    if (rootX != rootY) {
      p[rootX] += p[rootY];
      p[rootY] = rootX;
      return true;
    } else {
      return false;
    }
  }

  inline bool isFriend(int x, int y) {
    return calcRoot(x) == calcRoot(y);
  }

  inline int calcSize(int x) {
    return -p[calcRoot(x)];
  }
}; // class DisjointSet
} // namespace cs

namespace testing {

template<typename W>
gs::EdgeWeightedGraph<W> generateTree(int n) {
  gs::EdgeWeightedGraph<W> res;
  res.init(n);
  cs::DisjointSet dset;
  dset.init(n);
  for (int i = 1; i < n; ++i) {
    while (true) {
      int x = rand() % n;
      int y = rand() % n;
      if (!dset.isFriend(x, y)) {
        res.addUndirected(x, y, rand());
        dset.setFriend(x, y);
        break;
      }
    }
  }
  return res;
}
} // namespace testing
