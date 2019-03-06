/**
 * Code attached for convenience.
 */
namespace mu {

// Checks whether the number is in the form of 2^x
inline bool isPow2(int n) {
  return n && !(n & (n - 1));
}

// Computes the smallest 2^x which is not less than n.
inline int nextPow2(int n) {
  if (n <= 1) return 1;
  return isPow2(n) ? n : 1 << (32 - __builtin_clz(static_cast<unsigned int>(n)));
}
} // namespace mu

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
  inline void init(int n_, bool fixed = true) {
    this->n = n_;
    vs.reserve(fixed ? n : mu::nextPow2(n));
    vs.resize(n);
    fill(ALL(vs), 0);
  }

  inline void update(int i, const T &delta) {
    for (; i < n; i |= i + 1) {
      vs[i] += delta;
    }
  }

  inline T calc(int i) {
    if (i < 0) return T();
    T res = vs[i];
    for (i = transform(i); i >= 0; i = transform(i)) {
      res += vs[i];
    }
    return res;
  }

  inline T calcRange(int i, int j) {
    return calc(j) - calc(i - 1);
  }
};
}} // namespace cs::bit
