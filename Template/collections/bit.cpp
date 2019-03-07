namespace cs { namespace bit {

template <typename T>
class BinaryIndexedTree {
  int n;
  vector<T> vs;

  inline static int transform(int i) {
    return (i & (i + 1)) - 1;
  }

public:
  // Initializes
  inline void init(int _n) {
    this->n = _n;
    vs.resize(n);
    fill(vs.begin(), vs.end(), 0);
  }

  // Adds delta @ position i
  inline void update(int i, const T &delta) {
    for (; i < n; i |= i + 1) {
      vs[i] += delta;
    }
  }

  // Calculates sum from position 0 to position i
  inline T calc(int i) {
    if (i < 0) return T();
    T res = vs[i];
    for (i = transform(i); i >= 0; i = transform(i)) {
      res += vs[i];
    }
    return res;
  }

  // Calculates sum from position i to position j
  inline T calcRange(int i, int j) {
    return calc(j) - calc(i - 1);
  }
}; // class BinaryIndexedTree
}} // namespace cs::bit
