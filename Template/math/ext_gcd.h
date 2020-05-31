#include <algorithm>

using namespace std;

namespace math {

template<typename V = int32_t>
inline V extGcd(const V& a, const V& b, V& x0, V& x1) {
  if (!b) {
    x0 = 1;
    x1 = 0;
    return a;
  }
  V gcd = extGcd(b, a % b, x0, x1);
  swap(x0, x1);
  x1 -= a / b * x0;
  return gcd;
}

} // namespace math
