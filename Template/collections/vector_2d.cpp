namespace collections {

template <typename T> class Vector2D {
public:
  inline void init(int n, int m = -1) {
    lastOut.assign(n, -1);
    nxtOut.clear();
    values.clear();
    if (m > 0) {
      nxtOut.reserve(m);
      values.reserve(m);
    }
  }

  inline void add(int x, T v) {
    int edgeIdx = static_cast<int>(nxtOut.size());
    nxtOut.push_back(lastOut[x]);
    lastOut[x] = edgeIdx;
    values.push_back(v);
  }

  vector<int> lastOut, nxtOut;
  vector<T> values;
};

} // namespace collections
