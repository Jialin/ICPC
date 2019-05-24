namespace gs {

template<typename G>
class TopologicalSorter {
public:
  inline void calc(const G& g) {
    int n = g.n();
    order_.clear();
    inDegree_.resize(n);
    CLEAR(q_);
    FOR(i, 0, n) {
      inDegree_[i] = g.inDegree(i);
      if (!inDegree_[i]) q_.push(i);
    }
    for ( ; !q_.empty(); q_.pop()) {
      int u = q_.front();
      order_.push_back(u);
      for (int edgeIdx = g.lastOut(u); edgeIdx >= 0; edgeIdx = g.nxtOut(edgeIdx)) {
        int v = g.toIdx(edgeIdx);
        --inDegree_[v];
        if (!inDegree_[v]) q_.push(v);
      }
    }
  }

  inline const vector<int>& order() const { return order_; }

private:
  vector<int> order_, inDegree_;
  queue<int> q_;
};
} // namespace gs

using gs::TopologicalSorter;
