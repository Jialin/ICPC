namespace cs {

template<typename T>
class RMQ {
  int n;
  T* vs;
  vector<vector<int>> rmqIdx;

  static inline int highestBit(int n) {
    return 31 - __builtin_clz(n);
  }

  inline void _init() {
    int bit = highestBit(n);
    rmqIdx.resize(bit + 1);
    for (int i = 0; i <= bit; ++i) rmqIdx[i].resize(n - (1 << i) + 1);
    for (int i = 0; i < n; ++i) rmqIdx[0][i] = i;
    for (int i = 1; i <= bit; ++i) for (int j = n - (1 << i), k = j + (1 << (i - 1)); j >= 0; --j, --k) {
      int jIdx = rmqIdx[i - 1][j];
      int kIdx = rmqIdx[i - 1][k];
      rmqIdx[i][j] = vs[jIdx] < vs[kIdx] ? jIdx : kIdx;
    }
  }
public:
  inline void init(int _n, T* _vs) {
    n = _n;
    vs = _vs;
    _init();
  }

  inline void init(vector<T>& _vs) {
    init(static_cast<int>(_vs.size()), _vs.data());
  }

  inline int calcMinIdx(int lower, int upper) {
    int bit = highestBit(upper - lower + 1);
    int lowerIdx = rmqIdx[bit][lower];
    int upperIdx = rmqIdx[bit][upper - (1 << bit) + 1];
    return vs[lowerIdx] < vs[upperIdx] ? lowerIdx : upperIdx;
  }

  inline T& calcMin(int lower, int upper) {
    return vs[calcMinIdx(lower, upper)];
  }
}; // class RMQ
} // namespace cs

namespace trees {

template<typename G>
class LCA {
  vector<int> nodeIdx;
  vector<int> in, out;

  G* tree;
  cs::RMQ<int> depthRMQ;

  inline void dfs(int _depth, int u, int parent) {
    in[u] = static_cast<int>(depth.size());
    out[u] = in[u];
    depth.push_back(_depth);
    nodeIdx.push_back(u);
    for (int edgeIdx = tree->lastOut[u]; edgeIdx >= 0; edgeIdx = tree->nxtOut[edgeIdx]) {
      int v = tree->toIdx[edgeIdx];
      if (v == parent) continue;
      dfs(_depth + 1, v, u);
      out[u] = static_cast<int>(depth.size());
      depth.push_back(_depth);
      nodeIdx.push_back(u);
    }
  }
public:
  vector<int> depth;

  inline void init(G& _tree) {
    tree = &_tree;
    int n = tree->n, n3 = n * 3;
    depth.clear(); depth.reserve(n3);
    nodeIdx.clear(); nodeIdx.reserve(n3);
    in.clear(); in.reserve(n);
    out.clear(); out.reserve(n);
    dfs(0, 0, -1);
    depthRMQ.init(depth);
  }

  inline int calc(int x, int y) {
    int idx = depthRMQ.calcMinIdx(min(in[x], in[y]), max(out[x], out[y]));
    return nodeIdx[idx];
  }
}; // class LCA
} // namespace trees
