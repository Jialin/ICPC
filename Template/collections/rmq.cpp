namespace cs {

template<typename T, typename Compare = less<T>>
class RMQ {
public:
  inline RMQ(): cmp_(Compare()) {}

  inline void init(int n, T* vs) {
    n_ = n;
    vs_ = vs;
    init_();
  }

  inline void init(vector<T>& vs) {
    init(SIZE(vs), vs.data());
  }

  inline int calcIdx(int lower, int upper) const {
    int bit = highestBit_(upper - lower);
    int lowerIdx = rmqIdx_[bit][lower];
    int upperIdx = rmqIdx_[bit][upper - (1 << bit)];
    return cmp_(vs_[lowerIdx], vs_[upperIdx]) ? lowerIdx : upperIdx;
  }

  inline T& calc(int lower, int upper) {
    return vs_[calcIdx(lower, upper)];
  }

  inline int n() const { return n_; }

private:
  const Compare cmp_;
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
      rmqIdx_[i][j] = cmp_(vs_[jIdx], vs_[kIdx]) ? jIdx : kIdx;
    }
  }
}; // class RMQ
} // namespace cs
