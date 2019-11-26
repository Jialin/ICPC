// @autogen
namespace math {

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

} // namespace math