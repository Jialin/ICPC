#include <algorithm>
#include <cstddef>

using namespace std;

namespace math {

inline int gcd(int a, int b) {
  if (!a || !b) {
    return a | b;
  }
  size_t shift = __builtin_ctz(a | b);
  a >>= __builtin_ctz(a);
  do {
    b >>= __builtin_ctz(b);
    if (a > b) {
      swap(a, b);
    }
    b -= a;
  } while (b);
  return a << shift;
}

} // namespace math
