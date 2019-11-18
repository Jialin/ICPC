#define MAX_UINT_T UI64

namespace math {

namespace {

inline bool isProductOverflow(MAX_UINT_T a, MAX_UINT_T b) {
  if (!a || !b) {
    return false;
  }
  return a > numeric_limits<MAX_UINT_T>::max() / b;
}

inline void product(MAX_UINT_T a, MAX_UINT_T b, MAX_UINT_T &high,
                    MAX_UINT_T &low) {
  int halfL = numeric_limits<MAX_UINT_T>::digits >> 1;
  MAX_UINT_T halfMask = numeric_limits<MAX_UINT_T>::max() >> halfL;
  MAX_UINT_T aHigh = a >> halfL, aLow = a & halfMask;
  MAX_UINT_T bHigh = b >> halfL, bLow = b & halfMask;
  high = aHigh * bHigh;
  low = aLow * bLow;
  MAX_UINT_T ab = aHigh * bLow, ba = bHigh * aLow;
  high += (ab >> halfL) + (ba >> halfL);
  MAX_UINT_T lowHigh = (low >> halfL) + (ab & halfMask) + (ba & halfMask);
  high += lowHigh >> halfL;
  low = ((lowHigh & halfMask) << halfL) + (low & halfMask);
}

inline int sgn(MAX_UINT_T a, MAX_UINT_T b) {
  return a < b ? -1 : a == b ? 0 : 1;
}

} // namespace

/** sgn(a*b-c*d) */
inline int sgnUnsignedProduct(MAX_UINT_T a, MAX_UINT_T b, MAX_UINT_T c,
                              MAX_UINT_T d) {
  bool overflowAB = isProductOverflow(a, b);
  bool overflowCD = isProductOverflow(c, d);
  if (overflowAB) {
    if (overflowCD) {
      MAX_UINT_T high1, low1, high2, low2;
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

/** sgn(a/b-c/d) */
template <typename T> inline int sgnFraction(T a, T b, T c, T d) {
  assert(b && d);
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
      return -sgnUnsignedProduct(-a, d, -c, b);
    } else {
      return -1;
    }
  } else {
    if (c < 0) {
      return 1;
    } else {
      return sgnUnsignedProduct(a, d, c, b);
    }
  }
}

} // namespace math
