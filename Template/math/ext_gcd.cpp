/******************
 * TO BE VERIFIED.
 ******************/
namespace math {

inline int extGcd(int a, int b, int& x0, int& x1) {
  if (!b) {
    x0 = 1;
    x1 = 0;
    return a;
  }
  int gcd = extGcd(b, a % b, x0, x1);
  swap(x0, x1);
  x1 -= a / b * x0;
  return gcd;
}
} // namespace math
