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
