namespace gs {

class UnweightedGraph {
public:
  inline void init(int n) {
    n_ = n;
    lastOut_.resize(n);
    fill(lastOut_.begin(), lastOut_.end(), -1);
    nxtOut_.clear();
    toIdx_.clear();
  }

  inline void addDirected(int x, int y) {
    int edgeIdx = static_cast<int>(nxtOut_.size());
    nxtOut_.push_back(lastOut_[x]);
    toIdx_.push_back(y);
    lastOut_[x] = edgeIdx;
  }

  inline void addUndirected(int x, int y) {
    addDirected(x, y);
    addDirected(y, x);
  }

  inline int n() const { return n_; }
  inline int edgeCnt() const { return SIZE(toIdx_); }
  inline int lastOut(int x) const { return lastOut_[x]; }
  inline int nxtOut(int x) const { return nxtOut_[x]; }
  inline int toIdx(int x) const { return toIdx_[x]; }

private:
  int n_;
  vector<int> lastOut_, nxtOut_, toIdx_;
}; // class UnweightedGraph
} // namespace gs

namespace cs {

template<typename T>
class RMQ {
public:
  inline void init(int n, T* vs) {
    n_ = n;
    vs_ = vs;
    init_();
  }

  inline void init(vector<T>& vs) {
    init(static_cast<int>(vs.size()), vs.data());
  }

  inline int calcMinIdx(int lower, int upper) const {
    int bit = highestBit_(upper - lower);
    int lowerIdx = rmqIdx_[bit][lower];
    int upperIdx = rmqIdx_[bit][upper - (1 << bit)];
    return vs_[lowerIdx] < vs_[upperIdx] ? lowerIdx : upperIdx;
  }

  inline T& calcMin(int lower, int upper) const {
    return vs_[calcMinIdx(lower, upper)];
  }

  inline int n() const { return n_; }

private:
  int n_;
  T* vs_;
  vector<vector<int>> rmqIdx_;

  inline static int highestBit_(int n) { return 31 - __builtin_clz(n); }

  inline void init_() {
    int bit = highestBit_(n_);
    rmqIdx_.resize(bit + 1);
    for (int i = 0; i <= bit; ++i) rmqIdx_[i].resize(n_ - (1 << i) + 1);
    for (int i = 0; i < n_; ++i) rmqIdx_[0][i] = i;
    for (int i = 1; i <= bit; ++i) for (int j = n_ - (1 << i), k = j + (1 << (i - 1)); j >= 0; --j, --k) {
      int jIdx = rmqIdx_[i - 1][j];
      int kIdx = rmqIdx_[i - 1][k];
      rmqIdx_[i][j] = vs_[jIdx] < vs_[kIdx] ? jIdx : kIdx;
    }
  }
}; // class RMQ
} // namespace cs

namespace trees {

template<typename G>
class LCA {
public:
  inline void init(const G& _tree) {
    tree_ = &_tree;
    int n = tree_->n(), n2 = n << 1;
    depth_.clear(); depth_.reserve(n2);
    nodeIdx_.clear(); nodeIdx_.reserve(n2);
    in_.resize(n);
    out_.resize(n);
    parent_.resize(n);
    dfs_(0, 0, -1);
    rmq_.init(depth_);
  }

  inline int calc(int x, int y) const {
    if (out_[x] < in_[y]) {
      return parent_[nodeIdx_[rmq_.calcMinIdx(out_[x], in_[y] + 1)]];
    } else if (out_[y] < in_[x]) {
      return parent_[nodeIdx_[rmq_.calcMinIdx(out_[y], in_[x] + 1)]];
    } else {
      return in_[x] < in_[y] ? x : y;
    }
  }

  inline int n() const { return tree_->n(); }
  inline int nodeIdxSize() const { return SIZE(nodeIdx_); }
  inline int nodeIdx(int x) const { return nodeIdx_[x]; }
  inline int in(int x) const { return in_[x]; }
  inline int out(int x) const { return out_[x]; }
  inline int depth(int x) const { return depth_[x]; }
  inline int parent(int x) const { return parent_[x]; }

private:
  const G* tree_;
  vector<int> nodeIdx_, in_, out_, depth_, parent_;
  cs::RMQ<int> rmq_;

  inline void dfs_(int depth, int u, int parent) {
    parent_[u] = parent;
    in_[u] = SIZE(depth_);
    add_(depth, u);
    for (int edgeIdx = tree_->lastOut(u); edgeIdx >= 0; edgeIdx = tree_->nxtOut(edgeIdx)) {
      int v = tree_->toIdx(edgeIdx);
      if (v != parent) dfs_(depth + 1, v, u);
    }
    out_[u] = SIZE(depth_);
    add_(depth, u);
  }

  inline void add_(int depth, int u) {
    depth_.push_back(depth);
    nodeIdx_.push_back(u);
  }
}; // class LCA
} // namespace trees

namespace testing {

template<typename G>
string toDisplay(const trees::LCA<G>& lca) {
  ostringstream ss;
  ss << "order:"; FOR(i, 0, lca.nodeIdxSize()) ss << " " << lca.nodeIdx(i); ss << endl;
  FOR(i, 0, lca.n()) ss << "\t@" << i << ": [" << lca.in(i) << ", " << lca.out(i) + 1 << ")" << endl;
  return ss.str();
}
} // namespace testing
