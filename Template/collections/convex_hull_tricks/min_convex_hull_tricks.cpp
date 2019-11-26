// @autogen
namespace collections {

namespace {

namespace {

template <typename T> inline int sgn(T a, T b) {
  return a < b ? -1 : a == b ? 0 : 1;
}

template <typename UINT> inline bool isProductOverflow(UINT a, UINT b) {
  if (!a || !b) {
    return false;
  }
  static UINT maxUI = numeric_limits<UINT>::max();
  return a > maxUI / b;
}

template <typename UINT>
inline void product(UINT a, UINT b, UINT &high, UINT &low) {
  static int halfL = numeric_limits<UINT>::digits >> 1;
  static UINT halfMask = numeric_limits<UINT>::max() >> halfL;
  UINT aHigh = a >> halfL, aLow = a & halfMask;
  UINT bHigh = b >> halfL, bLow = b & halfMask;
  high = aHigh * bHigh;
  low = aLow * bLow;
  UINT ab = aHigh * bLow, ba = bHigh * aLow;
  high += (ab >> halfL) + (ba >> halfL);
  UINT lowHigh = (low >> halfL) + (ab & halfMask) + (ba & halfMask);
  high += lowHigh >> halfL;
  low = ((lowHigh & halfMask) << halfL) + (low & halfMask);
}

} // namespace

template <typename UINT>
inline int sgnProductUnsigned(UINT a, UINT b, UINT c, UINT d) {
  bool overflowAB = isProductOverflow(a, b);
  bool overflowCD = isProductOverflow(c, d);
  if (overflowAB) {
    if (overflowCD) {
      UINT high1, low1, high2, low2;
      product(a, b, high1, low1);
      product(c, d, high2, low2);
      int sgnHigh = sgn(high1, high2);
      return sgnHigh ? sgnHigh : sgn(low1, low2);
    } else {
      return 1;
    }
  } else {
    if (overflowCD) {
      return -1;
    } else {
      return sgn(a * b, c * d);
    }
  }
}
} // namespace

/** sgn(a/b-c/d) */
template <typename T, typename CMP_UINT_T>
inline int sgnFraction(T a, T b, T c, T d) {
  assert((a || b) && (c || d));
  if (b < 0) {
    a = -a;
    b = -b;
  }
  if (d < 0) {
    c = -c;
    d = -d;
  }
  if (a < 0) {
    if (c < 0) {
      return sgnProductUnsigned<CMP_UINT_T>(-c, b, -a, d);
    } else {
      return -1;
    }
  } else {
    if (c < 0) {
      return 1;
    } else {
      return sgnProductUnsigned<CMP_UINT_T>(a, d, c, b);
    }
  }
}

template <typename T, typename CMP_UINT_T = uint64_t>
class MinConvexHullTricks {
private:
  class Line {
  public:
    T a, b;
    mutable T num, den;

    inline Line(T a_, T b_) : a(a_), b(b_), num(0), den(1) {}

    inline bool operator<(const Line &o) const { return a > o.a; }

    inline bool operator<(T x) const {
      return sgnFraction<T, CMP_UINT_T>(num, den, x, 1) < 0;
    }
  };

  using Iterator = typename multiset<Line, less<>>::iterator;

  multiset<Line, less<>> lines_;

  inline void update(const Iterator &x, const Iterator &y) {
    if (y == lines_.end()) {
      x->num = 1;
      x->den = 0;
    } else if (x->a == y->a) {
      x->num = x->b < y->b ? 1 : -1;
      x->den = 0;
    } else {
      x->num = y->b - x->b;
      x->den = x->a - y->a;
    }
  }

  inline bool inOrder(const Iterator &x, const Iterator &y) const {
    return y == lines_.end() ||
           sgnFraction<T, CMP_UINT_T>(x->num, x->den, y->num, y->den) < 0;
  }

public:
  inline void init() { lines_.clear(); }

  inline void add(T a, T b) {
    auto y = lines_.emplace(a, b);
    // Remove following lines
    auto z = next(y);
    update(y, z);
    while (!inOrder(y, z)) {
      z = lines_.erase(z);
      update(y, z);
    }
    // Remove newly added line
    if (y == lines_.begin()) {
      return;
    }
    auto x = prev(y);
    update(x, y);
    if (!inOrder(x, y)) {
      y = lines_.erase(y);
      update(x, y);
    }
    // Remove preceeding lines
    for (y = x; x != lines_.begin() && !inOrder(--x, y); y = x) {
      update(x, lines_.erase(y));
    }
  }

  inline T query(T x) const {
    assert(!lines_.empty());
    auto l = lines_.lower_bound(x);
    return l->a * x + l->b;
  }

  inline int size() { return static_cast<int>(lines_.size()); }

  inline const multiset<Line, less<>> &lines() const { return lines_; }
};

} // namespace collections