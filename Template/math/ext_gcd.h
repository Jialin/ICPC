#include <tuple>

using namespace std;

namespace math {

// ax+by=gcd(a, b) and the return x, y satisfy:
//   abs(x)+abs(y) is minimum, if multiple minimums, x <= y
template<typename V = int32_t>
inline V extGcd(V a, V b, V& x, V& y) {
  x = 1;
  y = 0;
  V xTmp = 0;
  V yTmp = 1;
  while (b) {
    V q = a / b;
    tie(x, xTmp) = make_tuple(xTmp, x - q * xTmp);
    tie(y, yTmp) = make_tuple(yTmp, y - q * yTmp);
    tie(a, b) = make_tuple(b, a - q * b);
  }
  return a;
}

} // namespace math
