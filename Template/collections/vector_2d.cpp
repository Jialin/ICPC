namespace cs {

template<typename V>
class Vector2D {
public:
  inline void init(int n, int m = -1) {
    n_ = n;
    lastOut_.resize(n); fill(lastOut_.begin(), lastOut_.end(), -1);
    nxtOut_.clear(); if (m >= 0) nxtOut_.reserve(m);
    vs_.clear(); if (m >= 0) vs_.reserve(m);
  }

  inline void add(int x, const V& v) {
    int edgeIdx = SIZE(nxtOut_);
    nxtOut_.push_back(lastOut_[x]);
    lastOut_[x] = edgeIdx;
    vs_.push_back(v);
  }

  inline int n() const { return n_; }
  inline int lastOut(int x) const { return lastOut_[x]; }
  inline int nxtOut(int x) const { return nxtOut_[x]; }
  inline int value(int x) const { return vs_[x]; }

private:
  int n_;
  vector<int> lastOut_, nxtOut_;
  vector<V> vs_;
}; // class Vector2D
} // namespace cs
